#pragma once

namespace Mugen
{
	/**
	*	@class	Fraction
	*	@brief	�����N���X
	*/
	class Fraction
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		*/
		Fraction();

		/**
		 * @brief �R���X�g���N�^
		 * @param top ���q
		 * @param bottom ����
		*/
		Fraction(__int64 top, __int64 bottom);

		/**
		 * @brief �f�X�g���N�^
		*/
		~Fraction() = default;

		/**
		 * @brief ���q���擾����
		 * @return ���q
		*/
		__int64 GetTop() const;

		/**
		 * @brief ������擾����
		 * @return ����
		*/
		__int64 GetBottom() const;

		/**
		 * @brief ���q��ݒ肷��
		 * @param top ���q
		*/
		void SetTop(__int64 top);

		/**
		 * @brief �����ݒ肷��
		 * @param bottom ����
		*/
		void SetBottom(__int64 bottom);

		/**
		 * @brief �l�������l�Ƃ��Ď擾����
		 * @return �l
		*/
		long double GetValue() const;

		/**
		 * @brief �񕪂���(���ꂪ0�̏ꍇ�͉������Ȃ�)
		*/
		void Reduce();

		/**
		 * @brief ���Z���Z�q
		 * @param rhs �E��
		 * @return ���Z��������
		*/
		Fraction operator+(const Fraction& rhs);

		/**
		 * @brief ���Z���Z�q
		 * @param rhs �E��
		 * @return ���Z��������
		*/
		Fraction operator-(const Fraction& rhs);

		/**
		 * @brief ��Z���Z�q
		 * @param rhs �E��
		 * @return ��Z��������
		*/
		Fraction operator*(const Fraction& rhs);

		/**
		 * @brief ���Z���Z�q
		 * @param rhs �E��
		 * @return ���Z��������
		*/
		Fraction operator/(const Fraction& rhs);

	private:
		__int64 m_top;			//!< ���q
		__int64 m_bottom;		//!< ����
	};
}
