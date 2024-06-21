#pragma once
#include <Fraction.h>

namespace Mugen
{
	/**
	 * @brief トークンの種類を識別するタグ
	*/
	enum class TokenTag
	{
		Number,				//!< 数値
		UnaryOperator,		//!< 単項演算子
		BinaryOperator,		//!< 二項演算子
		BlockBegin,			//!< 括弧の始まり
		BlockEnd,			//!< 括弧の終わり
	};
	/**
	 * @brief 演算子の種類を識別するタグ
	*/
	enum class OperatorTag
	{
		Plus,				//!< 加算
		Minus,				//!< 減算
		Multiply,			//!< 乗算
		Divide,				//!< 除算
	};
	/**
	 * @brief 式を分解したトークン
	*/
	struct TOKEN
	{
		TokenTag tag;		//!< 識別タグ
		union
		{
			OperatorTag operatorTag;		//!< 演算子識別タグ
			Fraction value;					//!< 数値の値
		};
	};
}