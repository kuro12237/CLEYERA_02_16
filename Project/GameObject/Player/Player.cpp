#include "Player.h"
#include <EllysiaAudio/Audio.h>


//コンストラクタ
Player::Player() {

}

//初期化
void Player::Initialize() {

	//プレイヤーの体
	ModelManager::ModelLoadNormalMap();
	uint32_t playerHeadModel = ModelManager::LoadObjectFile("PlayerHead");
	ModelManager::ModelLoadNormalMap();
	uint32_t playerBodyModel = ModelManager::LoadObjectFile("PlayerBody");
	uint32_t playerHandModel = ModelManager::LoadObjectFile("PlayerHand");


	ModelManager::ModelLoadNormalMap();
	uint32_t hammerModel = ModelManager::LoadObjectFile("PlayerHammer");
	ModelManager::ModelLoadNormalMap();
	uint32_t sphereModel = ModelManager::LoadObjectFile("circle");

	for (int i = 0; i < BODY_AMOUNT_; i++) {
		model_[i] = std::make_unique<Game3dObject>();
		model_[i]->Create();
		worldTransform_[i].Initialize();
	}
	model_[0]->UseLight(true);
	model_[0]->SetlectModelPipeline(PHONG_MODEL);
	model_[0]->SetModel(playerHeadModel);
	model_[1]->UseLight(true);
	model_[1]->SetlectModelPipeline(PHONG_MODEL);
	model_[1]->SetModel(playerBodyModel);
	model_[2]->SetModel(playerHandModel);
	model_[2]->SetShininess(10.0f);

	// コライダーのビット処理
	SettingColliderBit();

	//ワールドトランスフォームの初期化
	

#pragma region ワールドトランスフォーム
	//SRT
	const float SCALE = 1.0f;
	worldTransform_[0].scale = {SCALE,SCALE,SCALE};
	//180度回転させたい
	const float offsetRotate = float(std::numbers::pi);
	worldTransform_[0].rotation = { 0.0f,offsetRotate,0.0f };
	worldTransform_[0].translate = { 0.0f,1.5f,0.0f };


	//体
	worldTransform_[1].scale = { SCALE,SCALE,SCALE };
	//180度回転させたい
	worldTransform_[1].rotation = { 0.0f,offsetRotate,0.0f };
	worldTransform_[1].translate = { 0.0f,0.0f,0.0f };

	//手
	const float HAND_SCALE = 2.0f;
	worldTransform_[2].scale = { HAND_SCALE,HAND_SCALE,HAND_SCALE };
	worldTransform_[2].rotation = { 0.0f,0.0f,0.0f };
	worldTransform_[2].translate = { 0.0f,0.0f,0.0f };

#pragma endregion

	//初速度
	initialVelocity_ = 0.4f;
	velocity_ = { 0.0f,initialVelocity_,0.0f };
	//加速度
	initialAcceleration_ = -0.03f;
	acceleration_ = { 0.0f,initialAcceleration_,0.0f };



	//ハンマー
	hammer_ = std::make_unique<Hammer>();
	hammer_->Initialize(hammerModel);

	//HitSphere
	hitSphere_ = std::make_unique<HitSphere>();
	hitSphere_->Initialize(sphereModel);


	// キルカウントの初期化
	killCount_ = 0;



	uint32_t auraModel= ModelManager::LoadObjectFile("PlayerAura");
	for (int i = 0; i < AURA_AMOUNT_; i++) {
		playerAura_[i] = std::make_unique<PlayerAura>();
		playerAura_[i]->Initialize(auraModel, worldTransform_[0].translate);
		//GameSceneを大胆にいじるの怖いから最初はスケールを0にして見えなくさせる
		//更新の時に元に戻して上げるのがいいかも
		//playerAura_[i]->SetScale({ 0.0f,0.0f,0.0f });
	}

	PlayerMoveParticle::Initialize();

	//ハンマーの振る音
	swingSEHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Player/Swing.wav");

	//ジャンプの音
	jumpSEHandle_= Audio::GetInstance()->LoadWave("Resources/Sounds/Player/Jump.wav");

	//着地の衝撃音
	impactSEHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Player/Impact.wav");

	//移動の音
	moveSEHandle_= Audio::GetInstance()->LoadWave("Resources/Sounds/Player/Move.wav");

	//攻撃パーティクル
	AttackParticle::Initialize();

}

#pragma region 更新処理のそれぞれの中身

/// <summary>
/// ジャンプ
/// </summary>
void Player::JumpPhese() {
	if (velocity_.y > 0.0f) {
		isJump_ = true;
		isFall_ = false;
	}
}

/// <summary>
/// 落下
/// </summary>
void Player::DropPhese() {
	//5.940で最大の高さ
	if (velocity_.y <= 0.0f) {
		isFall_ = true;
		isJump_ = false;
	}

}

/// <summary>
/// 急降下
/// </summary>
void Player::Dive() {
	if (worldTransform_[0].translate.y >= 3.0f) {
		if (isResetControl_ == true) {
			if ((Input::GetInstance()->PushKeyPressed(DIK_SPACE) == true) || (Input::GetInstance()->PushBottonPressed(XINPUT_GAMEPAD_B) == true)) {
				acceleration_.y = -0.08f;
				isControlMove_ = false;
				decideRadius_ = collisionRadius_;
				hitSphere_->SetRadius(decideRadius_);
				hammer_->SetIsPreAttack(true);
				//ハンマーを振る音
				Audio::GetInstance()->PlayWave(swingSEHandle_, false);

			}
		}
	}
}

//落下中
void Player::WhileDrop() {
	//ここでボタンを押すと攻撃になる
	//今はエンターキー
	//地面に付く寸前では受け付けない
	if (worldTransform_[0].translate.y >= 3.0f) {
		
		if (isResetControl_ == true) {
			if ((Input::GetInstance()->PushKeyPressed(DIK_SPACE) == true) || (Input::GetInstance()->PushBottonPressed(XINPUT_GAMEPAD_B) == true)) {
				hammer_->SetIsPreAttack(true);
				isControlMove_ = false;
				//
				decideRadius_ = collisionRadius_;
				hitSphere_->SetRadius(decideRadius_);

				//ハンマーを振る音
				Audio::GetInstance()->PlayWave(swingSEHandle_, false);

			}
		}
	}


	//isAttackがtrueになった時に当たり判定が出るようにしたい
	//preではまだ攻撃できないよ
	if (hammer_->GetIsAttack() == true) {
		//当たり判定のボックスが出る
		isHit_ = true;
	}
}

//リセット
void Player::Reset() {
	isResetControl_ = false;
	isJump_ = false;
	isFall_ = false;
	PlayerMoveParticle::Spown(GetWorldPosition());
	//ハンマーの位置をリセット
	resetRotateLodingTime_ += 1;

	//パーティクルを出す
	if (resetRotateLodingTime_ == 1) {
		PlayerMoveParticle::Spown(GetWorldPosition());
		Audio::GetInstance()->PlayWave(impactSEHandle_,false);
	}
	
	if (resetRotateLodingTime_ > RESET_TIME_) {
		isResetControl_ = true;
		hammer_->SetIsResetRotate(true);
		hammer_->SetIsAttack(false);
		hammer_->SetIsPreAttack(false);
		resetRotateLodingTime_ = 0;
		isControlMove_ = true;
		isReset_ = false;
		isHit_ = false;

	}
}

void Player::SettingSphere()
{
	SphereCollider::SetRadius(hitSphere_->GetRadius());
	CollisionManager::ColliderSpherePushBack(this);

}

void Player::SettingColliderBit()
{
	SphereCollider::SetCollosionAttribute(kCollisionAttributePlayer);
	SphereCollider::SetCollisionMask(kCollisionMaskPlayer);
	SphereCollider::SetID(playerHammerID);
}


#pragma endregion



Vector3 Player::GetWorldPosition() {
	Vector3 result = {};
	result.x = worldTransform_[0].matWorld.m[3][0];
	result.y = worldTransform_[0].matWorld.m[3][1];
	result.z = worldTransform_[0].matWorld.m[3][2];

	return result;
}


//更新
void Player::Update() {
	//何も押していない時は0.0f
	Vector3 translateMove = { 0.0f,0.0f,0.0f };
	Vector3 rotateMove = { 0.0f,0.0f,0.0f };

	PlayerMoveParticle::Update();

	if (isHit_&&!isHitPrev_)
	{
		AttackParticle::Spown(hitSphere_->GetWorldPosition(), { hitSphere_->GetRadius(),1.0f,1.0f });
	}
	isHitPrev_ = isHit_;
	AttackParticle::Update();
	//PushKeyPressedはTriggerのこと

#pragma region 移動
//上を押すと前に進む


	if (isControl_ == true) {
		if (isControlMove_ == true) {

			if ((Input::GetInstance()->PushKey(DIK_LSHIFT) == true) || Input::PushLShoulder()) {
				addSpeed_ = 3.0f;
				isDash_ = true;
			}
			else {
				addSpeed_ = 1.0f;
			}
			


			//上を押すと前に進む
			if ((Input::GetInstance()->PushKey(DIK_W) == true)|| Input::GetInstance()->PushBotton(XINPUT_GAMEPAD_DPAD_UP)) {
				dash_[Front].isDirection_=true;	
				dash_[Front].dashTime_ += 1;

				//人の歩くスピードBPM120なので
				//60/2
				/*walkTime_ += 1;
				if (walkTime_ == 1) {
					AudioManager::GetInstance()->AudioPlayWave(moveSEHandle_);
				}*/
				/*else if (walkTime_ > 30) {
					walkTime_ = 0;
				}*/
				//else {
				//	//BPM240でいいっしょ！
				//	dashTime_ += 1;
				//	if (dashTime_ == 1) {
				//		AudioManager::GetInstance()->AudioPlayWave(moveSEHandle_);
				//	}
				//	else if (dashTime_ > 15) {
				//		dashTime_ = 0;
				//	}
				//}
				
			}
			else {
				isDash_ = false;
				//walkTime_ = 0;
				dashTime_ = 0;
				dash_[Front].dashTime_ = 0;
				dash_[Front].isDirection_ = false;
			}

			//下を押すと後ろに進む
			if ((Input::GetInstance()->PushKey(DIK_S) == true) || Input::GetInstance()->PushBotton(XINPUT_GAMEPAD_DPAD_DOWN)) {
				dash_[Back].isDirection_ = true;
				//人の歩くスピードBPM120なので
				//60/2
				//if (isDash_ == false) {
				//	walkTime_ += 1;
				//	if (walkTime_ == 1) {
				//		Audio::GetInstance()->PlayWave(moveSEHandle_,false);
				//	}
				//	else if (walkTime_ > 30) {
				//		walkTime_ = 0;
				//	}
				//}
				//else {
				//	//BPM240でいいっしょ！
				//	dashTime_ += 1;
				//	if (dashTime_ == 1) {
				//		Audio::GetInstance()->PlayWave(moveSEHandle_,false);
				//	}
				//	else if (dashTime_ > 15) {
				//		dashTime_ = 0;
				//	}
				//}
			}
			else {
				walkTime_ = 0;
				dashTime_ = 0;
				dash_[Back].isDirection_ = false;
			}

			
			//右を押すと右に進む
			if ((Input::GetInstance()->PushKey(DIK_D) == true) || Input::GetInstance()->PushBotton(XINPUT_GAMEPAD_DPAD_RIGHT)) {
				dash_[Right].isDirection_=true;
				//人の歩くスピードBPM120なので
				//60/2
				
			}
			else {
				walkTime_ = 0;
				dashTime_ = 0;
				dash_[Right].isDirection_ = false;
			}

			//左を押すと左に進む
			if ((Input::GetInstance()->PushKey(DIK_A) == true) || Input::GetInstance()->PushBotton(XINPUT_GAMEPAD_DPAD_LEFT)) {
				dash_[Left].isDirection_=true;
				//人の歩くスピードBPM120なので
				//60/2
				
			}
			else {
				walkTime_ = 0;
				dashTime_ = 0;
				dash_[Left].isDirection_ = false;
			}



			if (dash_[Front].isDirection_ == true) {
				translateMove.z += MOVE_AMOUNT_ * addSpeed_;
				playerDirection_ = Front;
				if (isAction_ == false) {
					PlayerMoveParticle::Spown(GetWorldPosition());
				}
			}

			if (dash_[Back].isDirection_ == true) {
				translateMove.z -= MOVE_AMOUNT_ * addSpeed_;
				playerDirection_ = Back;
				if (isAction_ == false) {
					PlayerMoveParticle::Spown(GetWorldPosition());
				}
			}

			if (dash_[Right].isDirection_ == true) {
				translateMove.x += MOVE_AMOUNT_ * addSpeed_;
				playerDirection_ = Right;
				if (isAction_ == false) {
					PlayerMoveParticle::Spown(GetWorldPosition());
				}
			}

			if (dash_[Left].isDirection_ == true) {
				translateMove.x -= MOVE_AMOUNT_ * addSpeed_;
				playerDirection_ = Left;
				if (isAction_ == false) {
					PlayerMoveParticle::Spown(GetWorldPosition());
				}
			}

		}
	}


	//四方向に向く
	if (playerDirection_ == Right) {
		worldTransform_[0].rotation.y = float(std::numbers::pi);
	}
	if (playerDirection_ == Front) {
		worldTransform_[0].rotation.y = float(std::numbers::pi / 2.0f);
	}
	if (playerDirection_ == Left) {
		worldTransform_[0].rotation.y = 0.0f;
	}
	if (playerDirection_ == Back) {
		worldTransform_[0].rotation.y = (3.0f * float(std::numbers::pi)) / 2.0f;
	}

#pragma endregion

#pragma region 攻撃
	//スペースを押していない時は勿論行動していない時
	//押した瞬間
	if (isControl_ == true) {
		
		if ((Input::GetInstance()->PushKeyPressed(DIK_SPACE) == true) || (Input::GetInstance()->PushBottonPressed(XINPUT_GAMEPAD_B) == true) &&
			(isAction_ == false) && (isReset_ == false) && (isOnStage_ == true)) {
			hammer_->SetIsResetRotate(false);


			Audio::GetInstance()->PlayWave(jumpSEHandle_, false);
			isJump_ = true;
			isAction_ = true;
			isHit_ = false;
		}
		
		
	}
	

	//アクションを起こしている時が以下の文
	//加速度の計算でisActionが必要
	//ネストになっちゃいそう
	if (isAction_ == true) {
		//加速度の計算
		velocity_ = VectorTransform::Add(velocity_, acceleration_);
		translateMove.y = velocity_.y;

		//高さ
		height_ = worldTransform_[0].translate.y - 3.0f;
		//hitSphere用のサイズをここで決める
		//調べたところ5.940が最大点
		float t = height_ / 5.9f;
		const float MAX_SIZE = 7.0f;
		collisionRadius_ = t * MAX_SIZE;

		//ジャンプしている時
		//velocityは必ず0.0fより大きい
		JumpPhese();


		//落下のフラグを立てる
		//velocityは必ず0.0fより小さい
		DropPhese();


		//急降下

		if (isJump_ == true) {

			Dive();
		}


		//落下中
		if ((isFall_ == true)) {
			WhileDrop();
		}

	}



	//ステージ上にいる時だけ
	//めり込み厳禁
	//ここで攻撃が当たる感じ
	if (worldTransform_[0].translate.y < GROUND_TRANSLATE_ && isOnStage_ == true) {

		worldTransform_[0].translate.y = GROUND_TRANSLATE_ ;
		//velocity初期化忘れずに
		velocity_.y = initialVelocity_;
		acceleration_ = { 0.0f,-0.01f,0.0f };

		isReset_ = true;
		isAction_ = false;

	}

	//初期化
	if (isAction_ == false && isReset_ == true) {
		Reset();
	}





#pragma region ステージ上にいるかどうか
	if (isOnStage_ == false) {
		//初速度
		initialVelocity_ = -0.35f;
		velocity_ = { 0.0f,initialVelocity_,0.0f };
		//加速度
		initialAcceleration_ = 0.05f;
		acceleration_ = { 0.0f,initialAcceleration_,0.0f };
		velocity_ = VectorTransform::Add(velocity_, acceleration_);
		translateMove.y = velocity_.y;
	}

#pragma endregion




#pragma region デバッグ用

#ifdef _DEBUG
	bool isPreAttack = hammer_->GetIsPreAttack();
	bool isAttack = hammer_->GetIsAttack();
	bool isResetHammer = hammer_->GetIsResetRotate();

	if (ImGui::TreeNode("Player")){
		ImGui::SliderFloat3("Translate", &worldTransform_[0].translate.x, -10.0f, 10.0f);
		ImGui::InputFloat("Height", &height_);
		ImGui::InputFloat("CollisionRadius_", &collisionRadius_);
		ImGui::InputFloat("decideRadius_", &decideRadius_);
		ImGui::Checkbox("isAction", &isAction_);
		ImGui::Checkbox("isJump", &isJump_);
		ImGui::Checkbox("isFall", &isFall_);
		ImGui::Checkbox("isPreAttack", &isPreAttack);
		ImGui::Checkbox("isAttack", &isAttack);
		ImGui::Checkbox("HitBox", &isHit_);
		ImGui::Checkbox("ResetHammer", &isResetHammer);
		ImGui::Checkbox("IsOnStage", &isOnStage_);
		ImGui::InputInt("resetRotateLodingTime_", &resetRotateLodingTime_);
		ImGui::TreePop();
	}
#endif

#pragma endregion







#pragma endregion

	//計算
	//ベクトルの計算をするときはVectorTransformw.hをインクルード
	worldTransform_[0].translate = VectorTransform::Add(worldTransform_[0].translate, translateMove);
	worldTransform_[0].rotation = VectorTransform::Add(worldTransform_[0].rotation, rotateMove);

	//オフセット
	Vector3 newBodyTranslate= VectorTransform::Add(worldTransform_[0].translate, { 0.0f,BODY_TRANSLATE_OFFSET_Y_,0.0f });
	worldTransform_[1].translate = newBodyTranslate;
	worldTransform_[1].rotation = worldTransform_[0].rotation;

	//手
	Vector3 newHandTranslate = VectorTransform::Add(worldTransform_[0].translate, { 0.0f,0.0f,0.0f });
	worldTransform_[2].translate = newHandTranslate;
	worldTransform_[2].rotation = hammer_->GetRotateHammerHand();





	//ワールドトランスフォームの更新
	for (int i = 0; i < BODY_AMOUNT_; i++) {
		worldTransform_[i].UpdateMatrix();

	}
	
#pragma region ハンマー関係
	//当たり判定用のスフィア
	hitSphere_->SetPlayerWorldPosition(GetWorldPosition());
	//プレイヤーの向いている方向を設定
	hitSphere_->SetPlayerDirection_(playerDirection_);
	
	//当たり判定用
	hitSphere_->Update();


	//プレイヤーとハンマーが一緒に動く
	hammer_->SetTranslate(GetWorldPosition());
	//プレイヤーの向いている方向を設定
	hammer_->SetPlayerDirection(playerDirection_);
	hammer_->Update();

#pragma endregion

	// コライダーの設定
	SettingSphere();

#pragma region オーラ

	for (int i = 0; i < AURA_AMOUNT_; i++) {
		theta += 0.05f;
		const float HEIGHT_INTERVAL = 0.6f;
		const float AURA_INTERVAL = 1.5f;
		auraPosition_[i] = {
			worldTransform_[0].translate.x + std::sinf(theta + i * AURA_INTERVAL),
			worldTransform_[0].translate.y + i * HEIGHT_INTERVAL,
			worldTransform_[0].translate.z + std::cosf(theta + i * AURA_INTERVAL)
		};

		playerAura_[i]->SetPosition(auraPosition_[i]);
		playerAura_[i]->Update();

	}

#pragma endregion

}

void Player::OnCollision(uint32_t id)
{
	if (id == playerID) {
		return;
	}
	else if (id == enemyID) {

		if (isHit_) {

			// エネミーとの衝突処理

		}
	}
	else if (id == flagID) {
		return;
	}
	else if (id == groundID) {
		return;
	}
	else if (id == playerHammerID) {
		return;
	}
}

Vector3 Player::GetSphereColliderWorldPos()
{
	return hitSphere_->GetWorldPosition();
}

//描画
void Player::Draw(ViewProjection& camera) {
	//モデルの描画
	for (int i = 0; i < BODY_AMOUNT_-1; i++) {

		model_[i]->Draw(worldTransform_[i], camera);
		
	}
	

	

	hammer_->Draw(camera);

	
	

	//当たり判定用の円ポリが出る
	if (isHit_ == true) {
		if (hammer_->GetIsAttack() == true) {
			hitSphere_->Draw(camera);
		}
	}


	for (int i = 0; i < AURA_AMOUNT_; i++) {
		if (isAura_ == true) {
			playerAura_[i]->Draw(camera);
		}
		
	}
}

void Player::ParticleDraw(ViewProjection view)
{
	PlayerMoveParticle::Draw(view);

	AttackParticle::Draw(view);
}

//デストラクタ
Player::~Player() {


}
