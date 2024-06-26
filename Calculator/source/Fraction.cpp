#include <Fraction.h>
#include <numeric>

namespace Mugen
{
	Fraction::Fraction()
		:m_top(0)
		,m_bottom(0)
	{
	}
	Fraction::Fraction(__int64 top, __int64 bottom)
		:m_top(top)
		,m_bottom(bottom)
	{
	}
	__int64 Fraction::GetTop() const
	{
		return m_top;
	}
	__int64 Fraction::GetBottom() const
	{
		return m_bottom;
	}
	void Fraction::SetTop(__int64 top)
	{
		m_top = top;
	}
	void Fraction::SetBottom(__int64 bottom)
	{
		m_bottom = bottom;
	}
	long double Fraction::GetValue() const
	{
		if (0 == m_top)
		{
			return 0.0;
		}
		return static_cast<long double>(m_top) / static_cast<long double>(m_bottom);
	}
	void Fraction::Reduce()
	{
		// 分子か分母が0の時は何もしない
		if (0 == m_bottom || 0 == m_top)
		{
			return;
		}
		// 分子と分母の最大公約数
		const __int64 gcd = std::gcd(m_top, m_bottom);
		// 約分する
		m_top /= gcd;
		m_bottom /= gcd;
	}
	Fraction Fraction::operator+(const Fraction& rhs)
	{
		// 分母の最小公倍数
		const __int64 lcm = std::lcm(m_bottom, rhs.m_bottom);
		// それぞれ分母を最小公倍数で割った奴
		const __int64 divLhs = lcm / m_bottom;
		const __int64 divRhs = lcm / rhs.m_bottom;
		// 純粋な足し算
		Fraction retval(m_top * divLhs + rhs.m_top * divRhs, lcm);
		// 約分して既約分数で返す
		retval.Reduce();

		return retval;
	}

	Fraction Fraction::operator-(const Fraction& rhs)
	{
		// 分母の最小公倍数
		const __int64 lcm = std::lcm(m_bottom, rhs.m_bottom);
		// それぞれ分母を最小公倍数で割った奴
		const __int64 divLhs = lcm / m_bottom;
		const __int64 divRhs = lcm / rhs.m_bottom;
		// 純粋な引き算
		Fraction retval(m_top * divLhs - rhs.m_top * divRhs, lcm);
		// 約分して既約分数で返す
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator*(const Fraction& rhs)
	{
		// 純粋な引き算
		Fraction retval(m_top * rhs.m_top, m_bottom * rhs.m_bottom);
		// 約分して既約分数で返す
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator/(const Fraction& rhs)
	{
		// 純粋な引き算
		Fraction retval(m_top * rhs.m_bottom, m_bottom * rhs.m_top);
		// 約分して既約分数で返す
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator-()
	{
		return Fraction(-m_top, m_bottom);
	}
}
