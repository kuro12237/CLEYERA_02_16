#pragma once
#include "GameObject/EnemyManager/Type/Normal/MovePhaseState/INormalEnemyMovePhaseState.h"

class NormalEnemyMoveApproach : public INormalEnemyMovePhaseState {

public:

	void InitState(NormalEnemy* nEnemy) override;

	void UpdateState() override;

	void ExisState() override;

	void ChangeState(int nectPhase) override;
};

