#include "NormalEnemyMovePhaseDead.h"
#include "GameObject/EnemyManager/Type/Normal/NormalEnemy.h"



void NormalEnemyMovePhaseDead::InitState(NormalEnemy* nEnemy)
{
	nEnemy_ = nEnemy;
	
	if (nEnemy_->IsKilled()) {

		nEnemy_->SetDiffYSize(5.0f);
	}
}

void NormalEnemyMovePhaseDead::UpdateState()
{
	if (nEnemy_->IsKilled()) {
		nEnemy_->KilledMove();
	}

	if (nEnemy_->IsSuicide()) {
		nEnemy_->SuicideMove();
	}

	ExisState();
}

void NormalEnemyMovePhaseDead::ExisState()
{

	if (nEnemy_->GetProcessedDeadState()) {

		nEnemy_->SetDiffYSize(1.0f);
	}
	nEnemy_->SetProcessedDeadState(true);
}

void NormalEnemyMovePhaseDead::ChangeState(int nectPhase)
{
	ExisState();
	nEnemy_->SetMovePhaseNum(nectPhase);
}
