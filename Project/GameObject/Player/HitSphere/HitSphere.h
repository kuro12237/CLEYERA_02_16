#pragma once
#include "ViewProjection.h"
#include <WorldTransform.h>
#include <Game3dObject.h>


#include <memory>
#include <cmath>
#include <numbers>


#include "Vector3.h"

#include "CollisionManager.h"
#include "ColliderConfig.h"
#include "OBBCollider.h"
#include "SphereCollider.h"


class HitSphere {
public:
	//コンストラクタ
	HitSphere();

	//初期化
	void Initialize(uint32_t modelHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);

	//デストラクタ
	~HitSphere();


public:
	//アクセッサ

	void SetPlayerWorldPosition(Vector3 position) {
		this->playerPosition_ = position;
	}


	//半径・スケール
	const float GetRadius() {
		return radius_;
	}
	void SetRadius(float radius) {
		this->radius_ = radius;
	}


	void SetPlayerDirection_(uint32_t playerDirection) {
		this->playerDirection_= playerDirection;
	}

	Vector3 GetWorldPosition();

private:



private:
	//モデル
	std::unique_ptr<Game3dObject> model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_ = {};

	Vector3 offset = { 2.0f,0.0f,0.0f };

	//プレイヤーから受け取るデータ変数
	Vector3 playerPosition_ = {};
	uint32_t playerDirection_ = 0;

	//スケールにもなるよ
	//プレイヤーの高さが0の時は0.5にする
	//最大5.0くらいに
	float radius_ = 4.0f;

};

