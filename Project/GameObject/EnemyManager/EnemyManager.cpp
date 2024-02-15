#include "EnemyManager.h"
#include "Scene/GameScene.h"


// デストラクタ
EnemyManager::~EnemyManager() {};


// 初期化処理
void EnemyManager::Initialize(GameScene* scene, uint32_t time, uint32_t instance) {

	initEnemysCount_ = 1;
	intervalFrame_ = time;
	spawnTimer_ = 0;
	instanceEnemyCount_ = instance;
	thresholdEnemysCount_ = 3;

	gameScene_ = scene;

	//// 初期で沸かせる数
	//for (int i = 0; i < initEnemysCount_; i++) {
	//	gameScene_->SpawnEnemy();
	//}
}


// 更新処理
void EnemyManager::Update() {

	// Rで沸かせる
	if (Input::PushKeyPressed(DIK_R)) {
		gameScene_->SpawnEnemy();
	}

	// 定期的にエネミーを沸かせる処理
	SpawnEnemysPeriodically();
}


// 描画処理
void EnemyManager::Draw(ViewProjection view){}


// 定期的に敵を沸かせる処理
void EnemyManager::SpawnEnemysPeriodically() {

	spawnTimer_++;

	if (spawnTimer_ >= intervalFrame_) {

		spawnTimer_ = 0;

		for (int i = 0; i < instanceEnemyCount_; i++) {
			gameScene_->SpawnEnemy();
		}
	}
}

