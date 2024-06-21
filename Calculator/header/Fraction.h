#pragma once

namespace Mugen
{
	/**
	*	@class	Fraction
	*	@brief	分数クラス
	*/
	class Fraction
	{
	public:
		/**
		 * @brief コンストラクタ
		*/
		Fraction();

		/**
		 * @brief コンストラクタ
		 * @param top 分子
		 * @param bottom 分母
		*/
		Fraction(__int64 top, __int64 bottom);

		/**
		 * @brief デストラクタ
		*/
		~Fraction() = default;

		/**
		 * @brief 分子を取得する
		 * @return 分子
		*/
		__int64 GetTop() const;

		/**
		 * @brief 分母を取得する
		 * @return 分母
		*/
		__int64 GetBottom() const;

		/**
		 * @brief 分子を設定する
		 * @param top 分子
		*/
		void SetTop(__int64 top);

		/**
		 * @brief 分母を設定する
		 * @param bottom 分母
		*/
		void SetBottom(__int64 bottom);

		/**
		 * @brief 値を実数値として取得する
		 * @return 値
		*/
		long double GetValue() const;

		/**
		 * @brief 約分する(分母が0の場合は何もしない)
		*/
		void Reduce();

		/**
		 * @brief 加算演算子
		 * @param rhs 右辺
		 * @return 加算した結果
		*/
		Fraction operator+(const Fraction& rhs);

		/**
		 * @brief 減算演算子
		 * @param rhs 右辺
		 * @return 減算した結果
		*/
		Fraction operator-(const Fraction& rhs);

		/**
		 * @brief 乗算演算子
		 * @param rhs 右辺
		 * @return 乗算した結果
		*/
		Fraction operator*(const Fraction& rhs);

		/**
		 * @brief 除算演算子
		 * @param rhs 右辺
		 * @return 除算した結果
		*/
		Fraction operator/(const Fraction& rhs);

	private:
		__int64 m_top;			//!< 分子
		__int64 m_bottom;		//!< 分母
	};
}
