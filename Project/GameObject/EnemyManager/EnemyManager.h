#pragma once

#include "Enemy/Enemy.h"
#include "GameObject/RandomGenerator/RandomGenerator.h"

class GameScene;

/* Enemymanagerクラス */
class EnemyManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager() {};

	/// <summary>
	/// デストラクタ
	/// <summary>
	~EnemyManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(GameScene* scene, uint32_t time, uint32_t instance);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


#pragma region Get


#pragma endregion

#pragma region Set

#pragma endregion


private:

	/// <summary>
	/// 定期的に敵を沸かせる処理
	/// </summary>
	void SpawnEnemysPeriodically();

private:

	GameScene* gameScene_ = nullptr;

	// 初期沸く数
	int initEnemysCount_ = 0;

	// スポーンインターバル
	int intervalFrame_ = 0;

	// 一回に沸く数
	int instanceEnemyCount_ = 0;

	// スポーン時間
	int spawnTimer_ = 0;

	// エネミー最低限数
	int thresholdEnemysCount_ = 0;
};

