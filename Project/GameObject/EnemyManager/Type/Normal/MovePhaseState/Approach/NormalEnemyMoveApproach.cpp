#include "NormalEnemyMoveApproach.h"
#include "GameObject/EnemyManager/Type/Normal/NormalEnemy.h"



void NormalEnemyMoveApproach::InitState(NormalEnemy* nEnemy)
{
	nEnemy_ = nEnemy;
	nEnemy_->SettingDestinationPosition();
	nEnemy_->CalcDirection();
	nEnemy_->CalcRotate();
}

void NormalEnemyMoveApproach::UpdateState()
{
	nEnemy_->MoveApproach();

	if (nEnemy_->CalcDistance()) {
		ChangeState(Attack);
	}
}

void NormalEnemyMoveApproach::ExisState()
{


}

void NormalEnemyMoveApproach::ChangeState(int nectPhase)
{
	ExisState();
	nEnemy_->SetMovePhaseNum(nectPhase);

	// 死亡フェーズチェック
	nEnemy_->DeadPhaseCheck();
}
