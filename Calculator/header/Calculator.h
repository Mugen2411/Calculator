#pragma once
#include <ResultCode.h>
#include <TOKEN.h>
#include <list>
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

	private:
		const char* m_pExpression;					//!< 式
		const size_t m_length;						//!< 式の長さ
		size_t m_currentIndex;						//!< 現在参照している位置
		std::list<TOKEN> m_tokenList;				//!< トークンを入力順に格納するリスト
	};
}