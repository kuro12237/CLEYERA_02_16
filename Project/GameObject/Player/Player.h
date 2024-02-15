#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Game3dObject.h>

#include <Input.h>
#include <memory>
#include "Hammer/Hammer.h"
#include "HitSphere/HitSphere.h"
#include "PlayerDirection.h"
#include "Aura/PlayerAura.h"
#include "CollisionManager.h"
#include "OBBCollider.h"
#include "SphereCollider.h"
#include"MoveParticle/PlayerMoveParticle.h"
#include"GameObject/AttackParticle/AttackParticle.h"

class Player : public SphereCollider {
public:
	//コンストラクタ
	Player();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	// 衝突時コールバック関数
	void OnCollision(uint32_t id) override;


#pragma region Colliderで使うゲッター

	Vector3 GetSphereColliderWorldPos() override;

	float GetRadius() override { return this->decideRadius_; }

#pragma endregion 

	void Draw(ViewProjection& camera);

	void ParticleDraw(ViewProjection view);

	//デストラクタ
	~Player();




private:

	//ジャンプ中
	void JumpPhese();
	//落下
	void DropPhese();

	//急降下
	void Dive();

	//落下中
	void WhileDrop();

	//リセット
	void Reset();

public:

	const WorldTransform& GetWorldTransform() {
		return worldTransform_[0];
	}


	//初速度の設定
	void SetInitialVelocity(float initialVelocity) {
		this->initialVelocity_ = initialVelocity;
	}

	//落下処理に使う
	//ステージ上にいれば落ちない
	void SetGroundSize(Vector3 size) {
		this->groundSize_ = size;
	}


	//ステージ上にいるかどうかのアクセッサ
	void SetIsOnStage(bool isOnStage) {
		this->isOnStage_ = isOnStage;
	}
	bool GetIsOnStage() {
		return isOnStage_;
	}

	//操作できるか
	void SetIsControl(bool isControl) {
		this->isControl_ = isControl;
	}
	void SetGroundPosition(Vector3 position) {
		this->groundPosition_ = position;
	}



	//ワールド座標
	Vector3 GetWorldPosition();

	float GetCollisionRadius() {
		return decideRadius_;
	}

	
	void IsAura(bool isAura) {
		this->isAura_ = isAura;
	}


	/// <summary>
	/// 当たり判定で使うアクセッサ
	/// ハンマーを振り下ろし終わった時に出るよ
	/// </summary>
	bool GetIsHit(){
		return isHit_;
	}


	/// <summary>
	/// SphereColliderのセッティング
	/// </summary>
	void SettingSphere();

	/// <summary>
	/// Colliderのビットのセッティング
	/// </summary>
	void SettingColliderBit();



private:
	//ワールドトランスフォーム
	

	//モデル
	static const int BODY_AMOUNT_ = 3;
	std::unique_ptr<Game3dObject> model_[BODY_AMOUNT_] = { nullptr };
	WorldTransform worldTransform_[BODY_AMOUNT_] = {};

	float theta = 0.0f;
	//オフセット用
	const float BODY_TRANSLATE_OFFSET_Y_ = -1.3f;

	Vector3 rotateHand_ = {};

	//地面
	const float GROUND_TRANSLATE_ = 1.5f;

	//アクション(ジャンプ・落下・攻撃)をしているか
	bool isAction_ = false;

	//半径
	const float RADIUS_ = 0.5f;

#pragma region ジャンプ
	//ジャンプしているかどうか
	bool isJump_ = false;

	//初速度
	float initialVelocity_ = 0.55f;
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	//加速度
	float initialAcceleration_ = -0.01f;
	Vector3 acceleration_ = { 0.0f,0.0f,0.0f };

	//落ちているかどうか
	bool isFall_ = false;

	//高さ(地面基準)
	float height_ = 0.0f;
	//Sphereに代入する用のRadius
	const float INITIAL_COLLISION_RADIUS_ = 0.5f;
	float collisionRadius_ = 0.0f;
	float decideRadius_ = 0.0f;

#pragma endregion

	bool isHit_ = false;
	//ステージ上にいるか
	bool isOnStage_ = true;
	Vector3 groundPosition_ = {};
	Vector3 groundSize_ = {};
	//移動できるか。落ちた時に操作出来ないようにする
	bool isControl_ = true;
	//落下中別の方向に動かせないようにする
	bool isControlMove_ = true;

	bool isResetControl_ = true;

	//ハンマー
	std::unique_ptr<Hammer>hammer_ = nullptr;

	//リセット
	bool isReset_ = false;
	int32_t resetRotateLodingTime_ = 0;
	const int32_t RESET_TIME_ = 20;

	//移動
	const float MOVE_AMOUNT_ = 0.1f;
	const float ROTATE_AMOUNT_ = 0.05f;



	float addSpeed_ = 1.0f;
	struct PlayerDash {
		bool isDirection_ = false;
		int32_t dashCount_ = 0;
		int32_t dashTime_ = 0;
	};

	float dotDirection_ = 0.0f;
	static const int DIRECTION_AMOUNT_ = 4;
	PlayerDash dash_[DIRECTION_AMOUNT_] = {};
	bool idDashFront_ = false;
	int dashCount_=0;

	//当たり判定用
	std::unique_ptr<HitSphere> hitSphere_ = nullptr;
	//向き
	uint32_t playerDirection_ = Right;


	//オーラ
	static const int AURA_AMOUNT_ = 4;
	std::unique_ptr<PlayerAura> playerAura_[AURA_AMOUNT_] = { nullptr };
	Vector3 auraPosition_[AURA_AMOUNT_] = {};
	bool isAura_ = {};
	float auraTheta_ = 0.0f;

	// キルカウント
	int killCount_;

	XINPUT_STATE joyState_;
	int triggerButtonTime_ = 0;



	//ハンマーを振る音
	uint32_t swingSEHandle_ = 0u;

	//ジャンプ
	uint32_t jumpSEHandle_ = 0u;

	//地面に着地したときの衝撃音
	uint32_t impactSEHandle_ = 0u;

	//歩く・走る音
	uint32_t moveSEHandle_ = 0u;
	bool isDash_ = false;
	int32_t walkTime_ = 0;
	int32_t dashTime_ = 0;

	//particle
	bool isHitPrev_ = false;
};



