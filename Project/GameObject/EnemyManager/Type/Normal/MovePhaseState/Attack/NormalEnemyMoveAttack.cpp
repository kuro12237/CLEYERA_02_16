#include "NormalEnemyMoveAttack.h"
#include "GameObject/EnemyManager/Type/Normal/NormalEnemy.h"



void NormalEnemyMoveAttack::InitState(NormalEnemy* nEnemy)
{
	nEnemy_ = nEnemy;
	nEnemy_->SetIsRiseFunc(false);
	nEnemy_->SetAttackInitPos(nEnemy_->GetWorldPosition());
	nEnemy_->SetAttackMoveStart(false);
	nEnemy_->SetAttackMoveFinish(false);
}

void NormalEnemyMoveAttack::UpdateState()
{
	// �ŏ�1�b�ҋ@���Ă���U��������
	if (!nEnemy_->GetAttackMoveStart() && !nEnemy_->GetAttackMoveFinish()) {

		if (nEnemy_->WaitTime(60 * 1)) {

			// �U�������J�n
			nEnemy_->SetAttackMoveStart(true);

			// �U�������ɓ���t���O�𗧂Ă�
			nEnemy_->SetIsRiseFunc(true);

			// �㏸���v�t���[���̐ݒ�
			nEnemy_->SetRiseFrame(0, 60);

			// �C�[�W���O�Ɏg�����l
			nEnemy_->SetDiffPosY(0.0f);
		}
	}

	// �U������
	if (nEnemy_->GetAttackMoveStart()) {

		nEnemy_->MoveAttack();
	}

	// �U���I���t���O�������Ă�����V�[���ύX
	if (nEnemy_->GetAttackMoveFinish()) {

		if (nEnemy_->WaitTime(60 * 1)) {
			
			ChangeState(Approach);
		}
	}
}

void NormalEnemyMoveAttack::ExisState()
{
	// ���[�u�X�e�[�g�J�E���g�̉��Z
	nEnemy_->AddMoveStateCount();
}

void NormalEnemyMoveAttack::ChangeState(int nectPhase)
{
	ExisState();
	nEnemy_->SetMovePhaseNum(nectPhase);

	// ���S�t�F�[�Y�`�F�b�N
	nEnemy_->DeadPhaseCheck();
}
