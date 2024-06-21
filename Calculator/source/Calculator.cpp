#include "Calculator.h"
#include <cmath>

namespace Mugen
{
	Calculator::Calculator(const char* pExpression, size_t length)
		:m_pExpression(pExpression)
		,m_length(length)
		,m_currentIndex(0)
		, m_tokenList{}
	{
	}
	ResultCode Calculator::Calculate(Fraction& result)
	{
		// �����g�[�N���ɕ����������̂����X�g�ɕۑ�����
		ResultCode convertResult = _ConvertToTokenList();

		// �����Ɏ��s������I��
		if (ResultCode::Success != convertResult)
		{
			return convertResult;
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
			// �󔒂͓ǂݔ�΂�
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
		// �g�[�N����ʂ͐��l
		token.tag = TokenTag::Number;
		// �����Ǝw��
		__int64 mantissa = 0;
		__int64 exponent = 0;
		// �������ǂ���
		bool isInteger = true;
		// ���l�̒��o���I��������ǂ���
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
				// ���ɏ����_������̂ɂ܂������_��������\���G���[
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
		if (isInteger)
		{
			return ResultCode::Success;
		}
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
			// ���O�����l�����ʂ̏I��肾������񍀉��Z�q
			if (TokenTag::Number == lastTokenTag || TokenTag::BrockEnd == lastTokenTag)
			{
				token.tag = TokenTag::BinaryOperator;
			}
			// ����ȊO�Ȃ�P�����Z�q
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
			// �P�����Z�q�ɂȂ��Ă�����G���[
			if (token.tag == TokenTag::UnaryOperator)
			{
				return ResultCode::SyntaxError;
			}
			token.operatorTag = OperatorTag::Multiply;
			break;
		case '/':
			// �P�����Z�q�ɂȂ��Ă�����G���[
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
			token.tag = TokenTag::BrockBegin;
			break;
		case ')':
			token.tag = TokenTag::BrockEnd;
			break;
		default:
			return ResultCode::SyntaxError;
		}
		forwardIndex();
		return ResultCode::Success;
	}
}

