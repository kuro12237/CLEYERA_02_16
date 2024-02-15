#pragma once

#include "GameObject/EnemyManager/Type/IEnemyType.h"

#include "Input.h"
#include "Game3dObject.h"
#include "ModelManager.h"

#include "GameObject/RandomGenerator/RandomGenerator.h"

#include "GameObject/EnemyManager/Type/Normal/MovePhaseState/INormalEnemyMovePhaseState.h"
#include "GameObject/EnemyManager/Type/Normal/MovePhaseState/Approach/NormalEnemyMoveApproach.h"
#include "GameObject/EnemyManager/Type/Normal/MovePhaseState/Attack/NormalEnemyMoveAttack.h"
#include "GameObject/EnemyManager/Type/Normal/MovePhaseState/Dead/NormalEnemyMovePhaseDead.h"
#include "GameObject/EnemyManager/Type/Normal/MovePhaseState/Spawn/NormalEnemyModePhaseSpawn.h"

#include "GameObject/Flag/Flag.h"
#include "CollisionManager.h"
#include "OBBCollider.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Enemy;

/* NormalEnemyクラス */
class NormalEnemy : public IEnemyType, public OBBCollider {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalEnemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalEnemy() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(int modelID, int MringMode, Vector3 pos, std::array<ScopeVec3, 3> mapScope) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(bool isHit) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view) override;

	/// <summary>
	/// スポーン処理の終了フラグ
	/// </summary>
	bool IsSpanwFinished() override { return this->spawnFinish_; }

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	bool IsDead() override { return this->isDead_; }

	/// <summary>
	/// 死亡フラグの設定
	/// </summary>
	void SetIsDead(bool state) { this->isDead_ = state; }

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision(uint32_t id) override;

	/// <summary>
	/// 移動処理の更新処理
	/// </summary>
	void MovePhaseUpdate();

	/// <summary>
	/// Colliderの取得
	/// </summary>
	OBBCollider* GetOBBCollider() override { return this; }

	/// <summary>
	/// ムーブフェーズの設定
	/// </summary>
	void SetMovePhaseNum(int nextPhase) { this->phaseNum_ = nextPhase; }

	/// <summary>
	/// 死亡フェーズチェック
	/// </summary>
	void DeadPhaseCheck();


#pragma region Colliderで使うゲッター

	Vector3 GetWorldPosition() override;

	Vector3 GetSize() override { return this->size_; }

	Vector3 GetRotate() override { return this->wt_.rotation; }

#pragma endregion 


#pragma region  SpawnPhase で使うメンバ関数

	/// <summary>
	/// 沸いた時の移動処理
	/// </summary>
	void MoveSpawn();

	/// <summary>
	/// スポーン終了フラグの取得・設定
	/// </summary>
	bool GetSpawnFinish() { return this->spawnFinish_; }
	void SetSpawnFinish(bool state) { this->spawnFinish_ = state; }


	/// <summary>
	/// スポーンにかける所要フレーム
	/// </summary>
	void SetSpawnFrame(int nowFrame, int endFrame)
	{
		this->spawnNowFrame_ = nowFrame;
		this->spawnEndFrame_ = endFrame;
	}

	/// <summary>
	/// スポーン処理の初期座標の設定
	/// </summary>
	void SetSpawnInitPos(Vector3 pos) {
		this->spawnInitPos_ = pos;
	}

	/// <summary>
	/// // スポーン処理の初期回転の設定
	/// </summary>
	void SetSpawnInitRotate(Vector3 rotate) {
		this->spawnInitRotate_ = rotate;
	}

	/// <summary>
	/// 沸いてる最中は点滅する
	/// </summary>
	void FuncBlink();

	/// <summary>
	/// イージング
	/// </summary>
	float EaseOutCubic(float x);
	//float EaseOutCubic(float x);


#pragma endregion 


#pragma region ApproachPhase で使うメンバ関数

	/// <summary>
	/// 目的座標をの設定
	/// </summary>
	void SettingDestinationPosition();

	/// <summary>
	/// 移動処理
	/// </summary>
	void MoveApproach();

	/// <summary>
	/// エネミーの進行の計算
	/// </summary>
	void CalcDirection();

	/// <summary>
	/// エネミーの向きの計算
	/// </summary>
	void CalcRotate();

	/// <summary>
	/// 目標地点までの距離
	/// </summary>
	bool CalcDistance();

	/// <summary>
	/// 縦の波移動
	/// </summary>
	void CalcWaveVerticalMove();

#pragma endregion 


#pragma region  AttackPhase で使うメンバ関数

	/// <summary>
	/// 攻撃挙動処理
	/// </summary>
	void MoveAttack();

	/// <summary>
	/// 攻撃の上昇処理
	/// </summary>
	void AttackRise();

	/// <summary>
	/// 攻撃の落下処理
	/// </summary>
	void AttackFalling();

	/// <summary>
	/// 待機処理
	/// </summary>
	bool WaitTime(uint32_t waitTime);

	/// <summary>
	/// ムーブステートカウントの加算
	/// </summary>
	void AddMoveStateCount() { this->moveStateCount_ += 1; }

	/// <summary>
	/// Attack処理に入った時の初期座標の設定
	/// </summary>
	void SetAttackInitPos(Vector3 pos) { this->attackInitPos_ = pos; }

	/// <summary>
	/// 上昇にかける所要フレーム
	/// </summary>
	void SetRiseFrame(int nowFrame, int endFrame) 
	{ 
		this->riseNowFrame_ = nowFrame; 
		this->riseEndFrame_ = endFrame; 
	}

	/// <summary>
	/// 降下にかける所要フレーム
	/// </summary>
	void SetFallFrame(int nowFrame, int endFrame)
	{
		this->fallNowFrame_ = nowFrame;
		this->fallEndFrame_ = endFrame;
	}

	/// <summary>
	/// 攻撃処理に入るかのフラグ
	/// </summary>
	bool GetIsRiseFunc() { return this->isRiseFunc_; }
	void SetIsRiseFunc(bool state) { this->isRiseFunc_ = state; }

	/// <summary>
	/// 攻撃処理の開始フラグ
	/// </summary>
	bool GetAttackMoveStart() { return this->isAttackMoveStart_; }
	void SetAttackMoveStart(bool state) { this->isAttackMoveStart_ = state; }

	/// <summary>
	/// 攻撃処理の終了フラグ
	/// </summary>
	bool GetAttackMoveFinish() { return this->isAttackMoveFinish_; }
	void SetAttackMoveFinish(bool state) { this->isAttackMoveFinish_ = state; }

	/// <summary>
	/// イージング用加算数値
	/// </summary>
	void SetDiffPosY(float pos) { this->diffPosY_ = pos; }

	/// <summary>
	/// イージング
	/// </summary>
	float EaseOutQuart(float x);

#pragma endregion 


#pragma region  DeadPhase で使うメンバ関数

	/// <summary>
	/// 殺された時の移動処理
	/// </summary>
	void KilledMove();

	/// <summary>
	/// 自殺したときの移動処理
	/// </summary>
	void SuicideMove();

	/// <summary>
	/// 自殺フラグの取得
	/// </summary>
	bool IsSuicide() { return this->isSuicide_; }

	/// <summary>
	/// 殺されたかのフラグ
	/// </summary>
	bool IsKilled() { return this->isKilled_; }

	/// <summary>
	/// 差分Yサイズの設定
	/// </summary>
	void SetDiffYSize(float size) { this->diffSizeY_ = size; }

	/// <summary>
	/// 死亡処理を通ったか
	/// </summary>
	bool GetProcessedDeadState() { return this->isProcessedDeadState_; }

	/// <summary>
	/// 死亡処理を通ったかのフラグの設定
	/// </summary>
	void SetProcessedDeadState(bool state) { this->isProcessedDeadState_ = state; }

#pragma endregion 


private: // メンバ関数

	/// <summary>
	/// OBBColliderのセッティング
	/// </summary>
	void SettingCollider();

	/// <summary>
	/// Colliderのビットのセッティング
	/// </summary>
	void SettingColliderBit();

	/// <summary>
	/// エネミーとエネミーが衝突したとき
	/// </summary>
	void IsEnemyxEnemyHit();

private: // メンバ変数

	Enemy* enemy_ = nullptr;

	bool isHit_ = false;

	// モデル
	unique_ptr<Game3dObject> model_ = nullptr;

	// ワールド座標
	WorldTransform wt_{};

	// サイズ
	Vector3 size_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};

	// カラー
	Vector4 color_{};

	// フェーズ
	std::unique_ptr<INormalEnemyMovePhaseState> phaseArr_[4];
	int phaseNum_ = 0;
	int currentPhase_; // 現在のフェーズ
	int prevPhase_; // 前のフェーズ

	// 目標地点
	Vector3 DestinationPosition_{ 0.0f, 0.0f, 0.0f };

	// 死亡フラグ
	bool isDead_ = false;

	// スフィアの半径
	float radius_ = 0.0f;

	// 待機処理に使う変数
	bool waitFlag_ = false;
	int waitTimer_;

	// マップの範囲
	std::array<ScopeVec3, 3> mapScope_{};

	// ムーブステートカウント
	uint32_t moveStateCount_;
	uint32_t deadCount_;

	// エネミーとの衝突
	bool hitEnemy_;
	uint32_t hitEnemyTimer_;

	// 死亡フェーズに入るかのフラグ
	bool isDeadPhase_;

	// 差分Yサイズ
	float diffSizeY_ = 0.0f;

	// 死亡処理を通った回数
	bool isProcessedDeadState_ = 0;

	// 自殺フラグ
	bool isSuicide_;

	// 殺されたかのフラグ
	bool isKilled_;

	// 衝突したかのフラグ
	bool isCollision_;

	// モデル
	unique_ptr<Game3dObject> ringModel_ = nullptr;

	// ワールド座標
	WorldTransform ringWt_{};

	// Attack処理に入った時の初期座標
	Vector3 attackInitPos_{};

	// 上昇率
	float riseRate_ = 3.0f;

	// 上昇フレーム
	int riseNowFrame_ = 0;
	int riseEndFrame_ = 0;

	// 上昇攻撃処理にはいるフラグ
	bool isRiseFunc_ = false;

	// 差分座標
	float diffPosY_ = 0;

	// Attack処理に入った時の初期座標
	Vector3 fallingInitPos_{};

	// 下降フラグ
	bool isFallFunc_ = false;

	// 降下フレーム
	int fallNowFrame_ = 0;
	int fallEndFrame_ = 0;

	// 攻撃終了フラグ
	bool isAttackMoveStart_ = false;
	bool isAttackMoveFinish_ = false;

	// スポーン処理終了フラグ
	bool spawnFinish_;

	// スポーンフレーム
	int spawnNowFrame_ = 0;
	int spawnEndFrame_ = 0;

	// スポーン処理の初期座標
	Vector3 spawnInitPos_{};
	Vector3 spawnInitRotate_{};
};

