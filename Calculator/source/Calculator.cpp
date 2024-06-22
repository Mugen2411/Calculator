#include "Calculator.h"
#include <cmath>
#include <stack>

namespace Mugen
{
	Calculator::Calculator(const char* pExpression, size_t length)
		:m_pExpression(pExpression)
		, m_length(length)
		, m_currentIndex(0)
		, m_tokenList{}
	{
	}
	ResultCode Calculator::Calculate(Fraction& result)
	{
		// 式をトークンに分解したものをリストに保存する
		ResultCode convertResult = _ConvertToTokenList();

		// 分解に失敗したら終了
		if (ResultCode::Success != convertResult)
		{
			return convertResult;
		}

		// トークンに分解したものを逆ポーランド記法に並べ替える
		ResultCode reverseResult = _ConvertToReversePolish();

		// 並べ替えに失敗したら終了
		if (ResultCode::Success != reverseResult)
		{
			return reverseResult;
		}

		// 並べ替えたものを実際に計算する
		ResultCode calculateResult = _CalclateReversePolish(result);

		// 計算に失敗したら終了
		if (ResultCode::Success != calculateResult)
		{
			return calculateResult;
		}

		return ResultCode::Success;
	}
	ResultCode Calculator::_ConvertToTokenList()
	{
		TOKEN tmpToken = {};
		ResultCode resultCode = ResultCode::Success;
		do
		{
			switch (m_pExpression[m_currentIndex])
			{
			case ' ':
				forwardIndex();
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				resultCode = _MakeNumberToken(tmpToken);
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				resultCode = _MakeOperatorToken(tmpToken);
				break;
			case '(':
			case ')':
				resultCode = _MakeBrockToken(tmpToken);
				break;
			default:
				return ResultCode::SyntaxError;
			}
			if (resultCode != ResultCode::Success)
			{
				return resultCode;
			}
			m_tokenList.emplace_back(tmpToken);
		} while (m_length != m_currentIndex);
		return ResultCode::Success;
	}
	bool Calculator::forwardIndex()
	{
		do
		{
			++m_currentIndex;
			// 空白は読み飛ばす
			if (m_pExpression[m_currentIndex] == ' ')
			{
				continue;
			}
			else
			{
				break;
			}
		} while (m_currentIndex < m_length);
		if (m_currentIndex >= m_length)
		{
			return false;
		}
		return true;
	}
	ResultCode Calculator::_MakeNumberToken(TOKEN& token)
	{
		// トークン種別は数値
		token.tag = TokenTag::Number;
		// 仮数と指数
		__int64 mantissa = 0;
		__int64 exponent = 0;
		// 整数かどうか
		bool isInteger = true;
		// 数値の抽出が終わったかどうか
		bool isFinished = false;
		do
		{
			switch (m_pExpression[m_currentIndex])
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				mantissa *= 10;
				mantissa += m_pExpression[m_currentIndex] - '0';
				if (!isInteger)
				{
					++exponent;
				}
				break;
			case '.':
				// 既に小数点がいるのにまた小数点が来たら構文エラー
				if (!isInteger)
				{
					return ResultCode::SyntaxError;
				}
				isInteger = false;
				break;
			default:
				isFinished = true;
			}
			if (isFinished)
			{
				break;
			}
		} while (forwardIndex());

		token.value.SetTop(mantissa);
		__int64 bottom = 1;
		for (int i = 0; i < exponent; ++i)
		{
			bottom *= 10;
		}
		token.value.SetBottom(bottom);
		token.value.Reduce();
		return ResultCode::Success;
	}
	ResultCode Calculator::_MakeOperatorToken(TOKEN& token)
	{
		if (m_tokenList.empty())
		{
			token.tag = TokenTag::UnaryOperator;
		}
		else
		{
			const TokenTag lastTokenTag = m_tokenList.back().tag;
			// 直前が数値か括弧の終わりだったら二項演算子
			if (TokenTag::Number == lastTokenTag || TokenTag::BlockEnd == lastTokenTag)
			{
				token.tag = TokenTag::BinaryOperator;
			}
			// それ以外なら単項演算子
			else
			{
				token.tag = TokenTag::UnaryOperator;
			}
		}

		switch (m_pExpression[m_currentIndex])
		{
		case '+':
			token.operatorTag = OperatorTag::Plus;
			break;
		case '-':
			token.operatorTag = OperatorTag::Minus;
			break;
		case '*':
			// 単項演算子になっていたらエラー
			if (token.tag == TokenTag::UnaryOperator)
			{
				return ResultCode::SyntaxError;
			}
			token.operatorTag = OperatorTag::Multiply;
			break;
		case '/':
			// 単項演算子になっていたらエラー
			if (token.tag == TokenTag::UnaryOperator)
			{
				return ResultCode::SyntaxError;
			}
			token.operatorTag = OperatorTag::Divide;
			break;
		default:
			return ResultCode::SyntaxError;
		}
		forwardIndex();
		return ResultCode::Success;
	}
	ResultCode Calculator::_MakeBrockToken(TOKEN& token)
	{
		switch (m_pExpression[m_currentIndex])
		{
		case '(':
			token.tag = TokenTag::BlockBegin;
			break;
		case ')':
			token.tag = TokenTag::BlockEnd;
			break;
		default:
			return ResultCode::SyntaxError;
		}
		forwardIndex();
		return ResultCode::Success;
	}
	ResultCode Calculator::_ConvertToReversePolish()
	{
		std::stack<TOKEN> tokenStack;
		TOKEN lastOp = {};
		for (auto itr = m_tokenList.begin(); itr != m_tokenList.end();)
		{
			TOKEN cur = *itr;
			itr = m_tokenList.erase(itr);
			switch (cur.tag)
			{
			case TokenTag::Number:
				m_reversePolish.emplace(cur);
				break;

			case TokenTag::BlockBegin:
				tokenStack.emplace(cur);
				break;

			case TokenTag::UnaryOperator:
			case TokenTag::BinaryOperator:
				_ConvertOperatorToReversePolish(cur, tokenStack);
				break;

			case TokenTag::BlockEnd:
				while (1)
				{
					if (tokenStack.empty())
					{
						return ResultCode::SyntaxError;
					}
					lastOp = tokenStack.top();
					tokenStack.pop();
					if (lastOp.tag == TokenTag::BlockBegin)
					{
						break;
					}
					m_reversePolish.emplace(lastOp);
				}
				break;
			default:
				return ResultCode::SyntaxError;
				break;
			}
		}
		while (!tokenStack.empty())
		{
			TOKEN lastOp = tokenStack.top();
			m_reversePolish.emplace(lastOp);
			tokenStack.pop();
		}
		return ResultCode::Success;
	}
	ResultCode Calculator::_ConvertOperatorToReversePolish(const TOKEN& current, std::stack<TOKEN>& tokenStack)
	{
		TOKEN lastOp = {};

		if (tokenStack.empty())
		{
			tokenStack.emplace(current);
			return ResultCode::Success;
		}
		lastOp = tokenStack.top();

		const bool isUnary = lastOp.tag == TokenTag::UnaryOperator;
		const bool isBinary = lastOp.tag == TokenTag::UnaryOperator;
		if (isUnary || (isBinary && lastOp.operatorTag >= current.operatorTag))
		{
			m_reversePolish.emplace(lastOp);
			tokenStack.pop();
		}
		else
		{

		}
		tokenStack.push(current);
		return ResultCode::Success;
	}
	ResultCode Calculator::_CalclateReversePolish(Fraction& ans)
	{
		std::stack<TOKEN> stack;
		ResultCode resultCode;
		TOKEN result = {};
		TOKEN tmp = {};
		TOKEN lhs = {};
		TOKEN rhs = {};
		while (!m_reversePolish.empty())
		{
			tmp = m_reversePolish.front();
			m_reversePolish.pop();
			switch (tmp.tag)
			{
			case TokenTag::Number:
				stack.emplace(tmp);
				break;
			case TokenTag::UnaryOperator:
				if (stack.empty())
				{
					return ResultCode::SyntaxError;
				}
				lhs = stack.top();
				stack.pop();
				resultCode = _CalclateUnaryOperator(tmp, lhs, result);
				if (ResultCode::Success != resultCode)
				{
					return resultCode;
				}
				stack.emplace(result);
				break;
			case TokenTag::BinaryOperator:
				if (stack.size() < 2)
				{
					return ResultCode::SyntaxError;
				}
				rhs = stack.top();
				stack.pop();
				lhs = stack.top();
				stack.pop();
				resultCode = _CalclateBinaryOperator(tmp, lhs, rhs, result);
				if (ResultCode::Success != resultCode)
				{
					return resultCode;
				}
				stack.emplace(result);
				break;
			default:
				break;
			}
		}
		if (stack.size() != 1)
		{
			return ResultCode::SyntaxError;
		}
		ans = stack.top().value;
		return ResultCode::Success;
	}
	ResultCode Calculator::_CalclateUnaryOperator(const TOKEN operatorToken, const TOKEN& lhsToken, TOKEN& ans)
	{
		if (lhsToken.tag != TokenTag::Number)
		{
			return ResultCode::SyntaxError;
		}
		switch (operatorToken.operatorTag)
		{
		case OperatorTag::Plus:
			ans = lhsToken;
			break;
		case OperatorTag::Minus:
			ans = lhsToken;
			ans.value = -ans.value;
			break;
		default:
			return ResultCode::SyntaxError;
		}
		return ResultCode::Success;
	}

	ResultCode Calculator::_CalclateBinaryOperator(const TOKEN operatorToken, const TOKEN& lhsToken, const TOKEN& rhsToken, TOKEN& ans)
	{
		if (lhsToken.tag != TokenTag::Number)
		{
			return ResultCode::SyntaxError;
		}
		if (rhsToken.tag != TokenTag::Number)
		{
			return ResultCode::SyntaxError;
		}
		ans.tag = TokenTag::Number;
		ans.value = lhsToken.value;
		switch (operatorToken.operatorTag)
		{
		case OperatorTag::Plus:
			ans.value = ans.value + rhsToken.value;
			break;
		case OperatorTag::Minus:
			ans.value = ans.value - rhsToken.value;
			break;
		case OperatorTag::Multiply:
			ans.value = ans.value * rhsToken.value;
			break;
		case OperatorTag::Divide:
			if (0 == rhsToken.value.GetTop())
			{
				return ResultCode::DivideByZero;
			}
			ans.value = ans.value / rhsToken.value;
			break;
		default:
			return ResultCode::SyntaxError;
		}
		return ResultCode::Success;
	}
}

