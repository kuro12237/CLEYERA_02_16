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
	// 最初1秒待機してから攻撃処理へ
	if (!nEnemy_->GetAttackMoveStart() && !nEnemy_->GetAttackMoveFinish()) {

		if (nEnemy_->WaitTime(60 * 1)) {

			// 攻撃処理開始
			nEnemy_->SetAttackMoveStart(true);

			// 攻撃処理に入るフラグを立てる
			nEnemy_->SetIsRiseFunc(true);

			// 上昇所要フレームの設定
			nEnemy_->SetRiseFrame(0, 60);

			// イージングに使う数値
			nEnemy_->SetDiffPosY(0.0f);
		}
	}

	// 攻撃処理
	if (nEnemy_->GetAttackMoveStart()) {

		nEnemy_->MoveAttack();
	}

	// 攻撃終了フラグがたっていたらシーン変更
	if (nEnemy_->GetAttackMoveFinish()) {

		if (nEnemy_->WaitTime(60 * 1)) {
			
			ChangeState(Approach);
		}
	}
}

void NormalEnemyMoveAttack::ExisState()
{
	// ムーブステートカウントの加算
	nEnemy_->AddMoveStateCount();
}

void NormalEnemyMoveAttack::ChangeState(int nectPhase)
{
	ExisState();
	nEnemy_->SetMovePhaseNum(nectPhase);

	// 死亡フェーズチェック
	nEnemy_->DeadPhaseCheck();
}
