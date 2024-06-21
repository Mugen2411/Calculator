#pragma once
#include <Fraction.h>

namespace Mugen
{
	/**
	 * @brief �g�[�N���̎�ނ����ʂ���^�O
	*/
	enum class TokenTag
	{
		Number,				//!< ���l
		UnaryOperator,		//!< �P�����Z�q
		BinaryOperator,		//!< �񍀉��Z�q
		BlockBegin,			//!< ���ʂ̎n�܂�
		BlockEnd,			//!< ���ʂ̏I���
	};
	/**
	 * @brief ���Z�q�̎�ނ����ʂ���^�O
	*/
	enum class OperatorTag
	{
		Plus,				//!< ���Z
		Minus,				//!< ���Z
		Multiply,			//!< ��Z
		Divide,				//!< ���Z
	};
	/**
	 * @brief ���𕪉������g�[�N��
	*/
	struct TOKEN
	{
		TokenTag tag;		//!< ���ʃ^�O
		union
		{
			OperatorTag operatorTag;		//!< ���Z�q���ʃ^�O
			Fraction value;					//!< ���l�̒l
		};
	};
}