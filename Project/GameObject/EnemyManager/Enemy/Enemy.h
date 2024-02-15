#pragma once

#include "Input.h"
#include "Game3dObject.h"
#include "ModelManager.h"

#include "GameObject/EnemyManager/Type/IEnemyType.h"
#include "GameObject/EnemyManager/Type/Normal/NormalEnemy.h"

#include "GameObject/Flag/Flag.h"

#include "CollisionManager.h"


class Enemy {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(uint32_t modelEnemyHD, int MringMode, std::array<ScopeVec3, 3> mapScope, int typeNum,  Vector3 position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

	/// <summary>
	/// スポーン処理の終了フラグ
	/// </summary>
	bool IsSpanwFinished();

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	bool IsDead();

	/// <summary>
	/// Colliderの取得
	/// </summary>
	OBBCollider* GetOBBCollider();

	bool GetPlayerHammerIsHit() { return this->playerHammerIsHit_; }
	void SetPlayerHammerIsHit(bool isHit) {
		this->playerHammerIsHit_ = isHit;
	}

private:

	bool playerHammerIsHit_;

	// タイプ
	std::unique_ptr<IEnemyType> typeArr_[1];
	int currentType_;
};

