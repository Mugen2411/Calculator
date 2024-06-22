#pragma once
#include <ResultCode.h>
#include <TOKEN.h>
#include <list>
#include <queue>
#include <stack>

namespace Mugen
{
	class Fraction;
}
namespace Mugen
{
	/**
	 * @brief 計算機本体
	*/
	class Calculator
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param expression 式
		 * @param length 式の文字数
		*/
		Calculator(const char* pExpression, size_t length);
		/**
		 * @brief 計算を実行する
		 * @param result 計算結果の値
		 * @return リザルトコード
		*/
		ResultCode Calculate(Fraction& result);
	private:
		/**
		 * @brief 式からトークンに分解する
		 * @return リザルトコード
		*/
		ResultCode _ConvertToTokenList();

		/**
		 * @brief インデックスを前に進める
		 * @retval true 異常なし
		 * @retval false 式の最後の文字に到達した
		*/
		bool forwardIndex();

		/**
		 * @brief 式から数値トークンを取り出す
		 * @param token トークンの出力変数
		 * @return リザルトコード
		*/
		ResultCode _MakeNumberToken(TOKEN& token);

		/**
		 * @brief 式から演算子トークンを取り出す
		 * @param tokenList トークンの出力変数
		 * @return リザルトコード
		*/
		ResultCode _MakeOperatorToken(TOKEN& token);

		/**
		 * @brief 式から括弧トークンを取り出す
		 * @param tokenList トークンの出力変数
		 * @return リザルトコード
		*/
		ResultCode _MakeBrockToken(TOKEN& token);

		/**
		 * @brief 逆ポーランド記法に並べ替える
		 * @return リザルトコード
		*/
		ResultCode _ConvertToReversePolish();

		/**
		 * @brief 演算子を逆ポーランド記法に並べ替える
		 * @param current 現在引いているトークン
		 * @param tokenStack 演算子を溜めているスタック
		 * @return リザルトコード
		*/
		ResultCode _ConvertOperatorToReversePolish(const TOKEN& current, std::stack<TOKEN>& tokenStack);

		/**
		 * @brief 逆ポーランド記法に並べ替えた式を計算する
		 * @param ans 答えを格納する出力変数
		 * @return リザルトコード
		*/
		ResultCode _CalclateReversePolish(Fraction& ans);

		/**
		 * @brief 単項演算子の計算
		 * @param operatorToken 演算子
		 * @param lhsToken 左辺
		 * @param ans 答えを出力する変数
		 * @return リザルトコード
		*/
		ResultCode _CalclateUnaryOperator(const TOKEN operatorToken, const TOKEN& lhsToken, TOKEN& ans);

		/**
		 * @brief 二項演算子の計算
		 * @param operatorToken 演算子
		 * @param lhsToken 左辺
		 * @param rhsToken 右辺
		 * @param ans 答えを出力する変数
		 * @return リザルトコード
		*/
		ResultCode _CalclateBinaryOperator(const TOKEN operatorToken, const TOKEN& lhsToken, const TOKEN& rhsToken, TOKEN& ans);

	private:
		const char* m_pExpression;					//!< 式
		const size_t m_length;						//!< 式の長さ
		size_t m_currentIndex;						//!< 現在参照している位置
		std::list<TOKEN> m_tokenList;				//!< トークンを入力順に格納するリスト
		std::queue<TOKEN> m_reversePolish;			//!< トークンを逆ポーランド記法の順に格納するキュー
	};
}