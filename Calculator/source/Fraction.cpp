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
		// ���q�����ꂪ0�̎��͉������Ȃ�
		if (0 == m_bottom || 0 == m_top)
		{
			return;
		}
		// ���q�ƕ���̍ő����
		const __int64 gcd = std::gcd(m_top, m_bottom);
		// �񕪂���
		m_top /= gcd;
		m_bottom /= gcd;
	}
	Fraction Fraction::operator+(const Fraction& rhs)
	{
		// ����̍ŏ����{��
		const __int64 lcm = std::lcm(m_bottom, rhs.m_bottom);
		// ���ꂼ�ꕪ����ŏ����{���Ŋ������z
		const __int64 divLhs = lcm / m_bottom;
		const __int64 divRhs = lcm / rhs.m_bottom;
		// �����ȑ����Z
		Fraction retval(m_top * divLhs + rhs.m_top * divRhs, lcm);
		// �񕪂��Ċ��񕪐��ŕԂ�
		retval.Reduce();

		return retval;
	}

	Fraction Fraction::operator-(const Fraction& rhs)
	{
		// ����̍ŏ����{��
		const __int64 lcm = std::lcm(m_bottom, rhs.m_bottom);
		// ���ꂼ�ꕪ����ŏ����{���Ŋ������z
		const __int64 divLhs = lcm / m_bottom;
		const __int64 divRhs = lcm / rhs.m_bottom;
		// �����Ȉ����Z
		Fraction retval(m_top * divLhs - rhs.m_top * divRhs, lcm);
		// �񕪂��Ċ��񕪐��ŕԂ�
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator*(const Fraction& rhs)
	{
		// �����Ȉ����Z
		Fraction retval(m_top * rhs.m_top, m_bottom * rhs.m_bottom);
		// �񕪂��Ċ��񕪐��ŕԂ�
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator/(const Fraction& rhs)
	{
		// �����Ȉ����Z
		Fraction retval(m_top * rhs.m_bottom, m_bottom * rhs.m_top);
		// �񕪂��Ċ��񕪐��ŕԂ�
		retval.Reduce();

		return retval;
	}
	Fraction Fraction::operator-()
	{
		return Fraction(-m_top, m_bottom);
	}
}
