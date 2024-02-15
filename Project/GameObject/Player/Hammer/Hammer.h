#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Game3dObject.h>
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Game3dObject.h>

#include <memory>
#include <cmath>
#include <numbers>

class Hammer {
public:
	//コンストラクタ
	Hammer();

	//初期化
	void Initialize(uint32_t model);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);

	//デストラクタ
	~Hammer();

private:
	//ボタンが押されたとき
	void TriggerAttack();

	//リセット
	void Reset();


public:
	//アクセッサ
	void SetTranslate(Vector3 translate) {
		for (int i = 0; i < MODEL_AMOUNT_; i++) {
			this->worldTransform_[i].translate = translate;
		}
	}
	//攻撃する前の動き
	void SetIsPreAttack(bool isAttack) {
		this->isPreAttack_ = isAttack;
	}

	bool GetIsPreAttack() {
		return isPreAttack_;
	}

	//攻撃
	void SetIsAttack(bool isAttack) {
		this->isAttack_ = isAttack;
	}
	bool GetIsAttack() {
		return isAttack_;
	}

	void SetIsResetRotate(bool isResetRotate) {
		this->isResetRotate_ = isResetRotate;
	}
	bool GetIsResetRotate() {
		return isResetRotate_;
	}


	//プレイヤーの向いている方向
	void SetPlayerDirection(uint32_t direction) {
		this->playerDirection_=direction;
	}
	//ハンマーを持つ手の回転
	Vector3 GetRotateHammerHand() {
		return rotateHammerHand_;
	}


	//ワールド座標
	Vector3 GetWorldPosition();


private:
	
	const float INITIAL_ROTATE_ = 0.0f;

	//回転後のベクトル
	uint32_t playerDirection_ = 0u;

	//モデル
	//金属部分
	static const int MODEL_AMOUNT_ = 2;
	std::unique_ptr<Game3dObject> model_[MODEL_AMOUNT_] = { nullptr };

	const float ROTATE_AMOUNT_ = 0.1f;
	Vector3 rotateHammerHand_ = {};

	//ワールドトランスフォーム
	WorldTransform worldTransform_[MODEL_AMOUNT_] = {};

	//予備動作
	bool isPreAttack_ = false;

	//攻撃中
	bool isAttack_ = false;

	//リセット用
	bool isResetRotate_ = false;

};
