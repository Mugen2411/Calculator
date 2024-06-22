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

		/**
		 * @brief �t�|�[�����h�L�@�ɕ��בւ���
		 * @return ���U���g�R�[�h
		*/
		ResultCode _ConvertToReversePolish();

		/**
		 * @brief ���Z�q���t�|�[�����h�L�@�ɕ��בւ���
		 * @param current ���݈����Ă���g�[�N��
		 * @param tokenStack ���Z�q�𗭂߂Ă���X�^�b�N
		 * @return ���U���g�R�[�h
		*/
		ResultCode _ConvertOperatorToReversePolish(const TOKEN& current, std::stack<TOKEN>& tokenStack);

		/**
		 * @brief �t�|�[�����h�L�@�ɕ��בւ��������v�Z����
		 * @param ans �������i�[����o�͕ϐ�
		 * @return ���U���g�R�[�h
		*/
		ResultCode _CalclateReversePolish(Fraction& ans);

		/**
		 * @brief �P�����Z�q�̌v�Z
		 * @param operatorToken ���Z�q
		 * @param lhsToken ����
		 * @param ans �������o�͂���ϐ�
		 * @return ���U���g�R�[�h
		*/
		ResultCode _CalclateUnaryOperator(const TOKEN operatorToken, const TOKEN& lhsToken, TOKEN& ans);

		/**
		 * @brief �񍀉��Z�q�̌v�Z
		 * @param operatorToken ���Z�q
		 * @param lhsToken ����
		 * @param rhsToken �E��
		 * @param ans �������o�͂���ϐ�
		 * @return ���U���g�R�[�h
		*/
		ResultCode _CalclateBinaryOperator(const TOKEN operatorToken, const TOKEN& lhsToken, const TOKEN& rhsToken, TOKEN& ans);

	private:
		const char* m_pExpression;					//!< ��
		const size_t m_length;						//!< ���̒���
		size_t m_currentIndex;						//!< ���ݎQ�Ƃ��Ă���ʒu
		std::list<TOKEN> m_tokenList;				//!< �g�[�N������͏��Ɋi�[���郊�X�g
		std::queue<TOKEN> m_reversePolish;			//!< �g�[�N�����t�|�[�����h�L�@�̏��Ɋi�[����L���[
	};
}