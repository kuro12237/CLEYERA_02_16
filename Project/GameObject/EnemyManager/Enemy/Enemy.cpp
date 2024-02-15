#include "Enemy.h"



// コンストラクタ
Enemy::Enemy() {

	// 各タイプの配列
	typeArr_[Normal] = std::make_unique<NormalEnemy>();
}


// デストラクタ
Enemy::~Enemy() {}


// 初期化処理
void Enemy::Init(uint32_t modelEnemyHD, int MringMode, std::array<ScopeVec3, 3> mapScope, int typeNum,  Vector3 position) {

	// タイプのの初期化
	currentType_ = typeNum;
	typeArr_[currentType_]->Initialize(modelEnemyHD, MringMode, position, mapScope);
}


// 更新処理
void Enemy::Update() {

	// 各タイプの更新処理
	typeArr_[currentType_]->Update(playerHammerIsHit_);
}


// 描画処理
void Enemy::Draw(ViewProjection view) {
	
	// 各タイプの描画処理
	typeArr_[currentType_]->Draw(view);
}

// スポーン処理の終了フラグ
bool Enemy::IsSpanwFinished()
{
	return typeArr_[currentType_]->IsSpanwFinished();
}


// 死亡フラグの取得
bool Enemy::IsDead() {
	return typeArr_[currentType_]->IsDead();
}




// Colliderの取得
OBBCollider* Enemy::GetOBBCollider()
{
	return typeArr_[currentType_]->GetOBBCollider();
}
