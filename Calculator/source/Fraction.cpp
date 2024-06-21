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
		// •ªq‚©•ª•ê‚ª0‚Ì‚Í‰½‚à‚µ‚È‚¢
		if (0 == m_bottom || 0 == m_top)
		{
			return;
		}
		// •ªq‚Æ•ª•ê‚ÌÅ‘åŒö–ñ”
		const __int64 gcd = std::gcd(m_top, m_bottom);
		// –ñ•ª‚·‚é
		m_top /= gcd;
		m_bottom /= gcd;
	}
	Fraction Fraction::operator+(const Fraction& rhs)
	{
		// •ª•ê‚ÌÅ¬Œö”{”
		const __int64 lcm = std::lcm(m_bottom, rhs.m_bottom);
		// ‚»‚ê‚¼‚ê•ª•ê‚ğÅ¬Œö”{”‚ÅŠ„‚Á‚½“z
		const __int64 divLhs = lcm / m_bottom;
		const __int64 divRhs = lcm / rhs.m_bottom;
		// ƒˆ‚È‘«‚µZ
		Fraction retval(m_top * divLhs + rhs.m_top * divRhs, lcm);
		// –ñ•ª‚µ‚ÄŠù–ñ•ª”‚Å•Ô‚·
		retval.Reduce();

		return retval;
	}

	Fraction Fraction::operator-(const Fraction& rhs)
	{
		// •ª•ê‚ÌÅ¬Œö”{”
		const __int64 lcm = std::lcm(m_bottom, rhs.m_bottom);
		// ‚»‚ê‚¼‚ê•ª•ê‚ğÅ¬Œö”{”‚ÅŠ„‚Á‚½“z
		const __int64 divLhs = lcm / m_bottom;
		const __int64 divRhs = lcm / rhs.m_bottom;
		// ƒˆ‚Èˆø‚«Z
		Fraction retval(m_top * divLhs - rhs.m_top * divRhs, lcm);
		// –ñ•ª‚µ‚ÄŠù–ñ•ª”‚Å•Ô‚·
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator*(const Fraction& rhs)
	{
		// ƒˆ‚Èˆø‚«Z
		Fraction retval(m_top * rhs.m_top, m_bottom * rhs.m_bottom);
		// –ñ•ª‚µ‚ÄŠù–ñ•ª”‚Å•Ô‚·
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator/(const Fraction& rhs)
	{
		// ƒˆ‚Èˆø‚«Z
		Fraction retval(m_top * rhs.m_bottom, m_bottom * rhs.m_top);
		// –ñ•ª‚µ‚ÄŠù–ñ•ª”‚Å•Ô‚·
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator-()
	{
		return Fraction(-m_top, m_bottom);
	}
}
