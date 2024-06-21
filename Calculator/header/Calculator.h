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
	 * @brief �v�Z�@�{��
	*/
	class Calculator
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 * @param expression ��
		 * @param length ���̕�����
		*/
		Calculator(const char* pExpression, size_t length);
		/**
		 * @brief �v�Z�����s����
		 * @param result �v�Z���ʂ̒l
		 * @return ���U���g�R�[�h
		*/
		ResultCode Calculate(Fraction& result);
	private:
		/**
		 * @brief ������g�[�N���ɕ�������
		 * @return ���U���g�R�[�h
		*/
		ResultCode _ConvertToTokenList();

		/**
		 * @brief �C���f�b�N�X��O�ɐi�߂�
		 * @retval true �ُ�Ȃ�
		 * @retval false ���̍Ō�̕����ɓ��B����
		*/
		bool forwardIndex();

		/**
		 * @brief �����琔�l�g�[�N�������o��
		 * @param token �g�[�N���̏o�͕ϐ�
		 * @return ���U���g�R�[�h
		*/
		ResultCode _MakeNumberToken(TOKEN& token);

		/**
		 * @brief �����牉�Z�q�g�[�N�������o��
		 * @param tokenList �g�[�N���̏o�͕ϐ�
		 * @return ���U���g�R�[�h
		*/
		ResultCode _MakeOperatorToken(TOKEN& token);

		/**
		 * @brief �����犇�ʃg�[�N�������o��
		 * @param tokenList �g�[�N���̏o�͕ϐ�
		 * @return ���U���g�R�[�h
		*/
		ResultCode _MakeBrockToken(TOKEN& token);

	private:
		const char* m_pExpression;					//!< ��
		const size_t m_length;						//!< ���̒���
		size_t m_currentIndex;						//!< ���ݎQ�Ƃ��Ă���ʒu
		std::list<TOKEN> m_tokenList;				//!< �g�[�N������͏��Ɋi�[���郊�X�g
	};
}