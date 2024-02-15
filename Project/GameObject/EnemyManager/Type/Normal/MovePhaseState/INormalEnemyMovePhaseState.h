#pragma once

enum NormalEnemyPhase {
	Spawn,
	Approach,
	Attack,
	Dead,
};

class NormalEnemy;

class INormalEnemyMovePhaseState {

public:

	INormalEnemyMovePhaseState() {};

	~INormalEnemyMovePhaseState() {};

	virtual void InitState(NormalEnemy* nEnemy) = 0;

	virtual void UpdateState() = 0;

	virtual void ExisState() = 0;

	virtual void ChangeState(int nextPhase) = 0;

protected:

	NormalEnemy* nEnemy_;

};