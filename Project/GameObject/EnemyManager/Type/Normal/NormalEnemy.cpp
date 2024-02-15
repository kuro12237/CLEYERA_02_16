#include "NormalEnemy.h"
#include "GameObject/EnemyManager/Enemy/Enemy.h"
#include "ViewProjection.h"


// コンストラクタ
NormalEnemy::NormalEnemy()
{
	// 各フェーズの配列
	phaseArr_[Spawn] = std::make_unique<NormalEnemyModePhaseSpawn>();
	phaseArr_[Approach] = std::make_unique<NormalEnemyMoveApproach>();
	phaseArr_[Attack] = std::make_unique< NormalEnemyMoveAttack>();
	phaseArr_[Dead] = std::make_unique<NormalEnemyMovePhaseDead>();
	phaseNum_ = Spawn;
}


// 初期化処理
void NormalEnemy::Initialize(int modelID, int MringMode, Vector3 pos, std::array<ScopeVec3, 3> mapScope)
{
	// モデルの設定
	model_ = make_unique<Game3dObject>();
	model_->Create();
	model_->SetModel(modelID);
	//modelの質感設定
	model_->UseLight(false);
	model_->SetShininess(1280.0f);
	model_->SetlectModelPipeline(PHONG_NORMAL_MODEL);
	// ワールドトランスフォームの設定
	wt_.Initialize();
	wt_.translate = pos;
	wt_.rotation.x = -2.0f;
	wt_.UpdateMatrix();

	// リングモデルの設定
	ringModel_ = make_unique<Game3dObject>();
	ringModel_->Create();
	ringModel_->SetModel(MringMode);
	//ringModel_->UseLight(true);

	// ワールドトランスフォームの設定
	ringWt_.Initialize();
	ringWt_.parent = &wt_;
	ringWt_.translate.y += 2.0f;
	ringWt_.UpdateMatrix();

	// 移動先の設定　今は原点
	DestinationPosition_ = { 0.0f, 2.0f, 0.0f };

	// 速度の設定
	velocity_ = { 0.0f, 0.0f, 0.0f };

	// カラーの設定
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// マップの範囲
	mapScope_ = mapScope;

	// ムーブステートカウント
	moveStateCount_ = 0;
	deadCount_ = 2;

	// エネミーとの衝突判定フラグ
	hitEnemy_ = false;

	// 自殺フラグ
	isSuicide_ = false;

	// 殺されたかのフラグ
	isKilled_ = false;

	// 衝突したかのフラグ
	isCollision_ = false;

	// 差分Yサイズ
	diffSizeY_ = 0.0f;

	// 自殺フラグ
	isSuicide_ = false;

	////////////// ムーブフェーズの初期化に入るから、値の設定はここより上で設定する

	// ムーブフェーズの設定
	currentPhase_ = phaseNum_;
	phaseArr_[currentPhase_]->InitState(this);
	phaseArr_[Approach]->InitState(this);
	phaseArr_[Approach]->UpdateState();

	// コライダーのビットの設定
	SettingColliderBit();
}


// 更新処理
void NormalEnemy::Update(bool isHit)
{
	wt_.UpdateMatrix();
	ringWt_.UpdateMatrix();

	isHit_ = isHit;

	// 移動処理の更新処理
	MovePhaseUpdate();

	// 既定値回数分ステートパターンを回っていたら死亡フラグを立てる
	// エネミーが沸きすぎないようにするため
	if (moveStateCount_ >= deadCount_) {
		isDeadPhase_ = true;
		isSuicide_ = true;
	}


	if (Input::PushKeyPressed(DIK_K)) {
		isDeadPhase_ = true;
	}


	// OBBColliderのセッティング
	SettingCollider();
}


// 描画処理
void NormalEnemy::Draw(ViewProjection view)
{
	model_->Draw(wt_, view);

	if (isKilled_) {
		ringModel_->Draw(ringWt_, view);
	}
}


// 衝突時コールバック関数
void NormalEnemy::OnCollision(uint32_t id)
{
	if (id == playerID) {
		return;
	}
	else if (id == enemyID) {
		IsEnemyxEnemyHit();
		return;
	}
	else if (id == flagID) {
		return;
	}
	else if (id == groundID) {
		return;
	}
	else if (id == playerHammerID) {

		// 衝突するか
		if (!isCollision_) {

			if (isHit_) {
				isDeadPhase_ = true;
				isKilled_ = true;
				DeadPhaseCheck();
			}
		}
	}
}


// 移動処理の更新処理
void NormalEnemy::MovePhaseUpdate()
{
	if (!isDead_) {

		// フェーズチェック
		prevPhase_ = currentPhase_;
		currentPhase_ = phaseNum_;

		// フェーズ変更チェック
		if (prevPhase_ != currentPhase_) {

			// 変更していたら初期化処理
			phaseArr_[currentPhase_]->InitState(this);
		}

		// 更新処理
		phaseArr_[currentPhase_]->UpdateState();
	}
}


// 死亡フェーズチェック
void NormalEnemy::DeadPhaseCheck()
{
	if (isDeadPhase_) {
		phaseNum_ = Dead;
	}
}


// ワールド座標の取得
Vector3 NormalEnemy::GetWorldPosition()
{
	Vector3 worldPos = {
		wt_.matWorld.m[3][0],
		wt_.matWorld.m[3][1],
		wt_.matWorld.m[3][2],
	};
	return worldPos;
}


#pragma region  SpawnPhase で使うメンバ関数

// 沸いた時の移動処理
void NormalEnemy::MoveSpawn()
{
	// スポーン処理の終了フラグが立っていたら早期リターン
	if (spawnFinish_) {
		return;
	}

	// 上昇目的座標の設定
	float desti = 2.2f;

	// 上昇目的座標へのイージング
	if (spawnNowFrame_ <= spawnEndFrame_) {
		spawnNowFrame_++;
	}
	wt_.translate.y =
		spawnInitPos_.y + (desti - spawnInitPos_.y) * EaseOutCubic(float(spawnNowFrame_) / float(spawnEndFrame_));
	wt_.rotation.x =
		spawnInitRotate_.x + (0.0f - spawnInitRotate_.x) * EaseOutCubic(float(spawnNowFrame_) / float(spawnEndFrame_));
	color_.w =
		0.0f + (1.0f - 0.0f) * EaseOutCubic(float(spawnNowFrame_) / float(spawnEndFrame_));
	model_->SetColor(color_);

	// 終了したらスポーン処理の終了フラグを折る
	if (spawnNowFrame_ >= spawnEndFrame_) {

		color_.w = 1.0f;
		model_->SetColor(color_);
		spawnFinish_ = true;
		model_->UseLight(true);
	}
}


// 沸いてる最中は点滅する
void NormalEnemy::FuncBlink()
{
	// 透明度を変化させて沸いてるのを分かりやすくする
	if (spawnNowFrame_ % 6 == 0) {

		if (color_.w == 1.0f) {
			color_.w = 0.5f;
		}
		else if (color_.w == 0.5f) {
			color_.w = 1.00;
		}
		model_->SetColor(color_);
	}
}


// イージング
float NormalEnemy::EaseOutCubic(float x)
{
	return 1.0f - std::pow(1.0f - x, 3.0f);
}
//float NormalEnemy::EaseOutCubic(float x)
//{
//	return 1.0f - std::pow(1.0f - x, 3.0f);
//}

#pragma endregion 


#pragma region  AttackPhase で使うメンバ関数

// 目的座標をの設定
void NormalEnemy::SettingDestinationPosition()
{
	// どのマップに向かうか決める
	// 配列のどの番号にアクセスするかを単純にランダムで決める
	Scope AS = { 0.0f, 3.0f };
	int Index = int(RandomGenerator::getRandom(AS));

	// マップの中のどの地点に向かうか、決めたマップの範囲をスコープにして
	// ランダムで決める
	Vector3 MS = RandomGenerator::getRandom(mapScope_[Index]);

	// このままだと地面に埋もれちゃうので、値を直書きで入れる。
	// 正直あんま良くない
	MS.y = 2.2f;

	// 決まった範囲の中の座標を目的地の座標に入れる
	DestinationPosition_ = MS;
}


// 移動処理
void NormalEnemy::MoveApproach()
{
	CalcDirection();
	CalcRotate();
	CalcWaveVerticalMove();
	wt_.translate = VectorTransform::Add(wt_.translate, velocity_);
}


// エネミーの進行の計算
void NormalEnemy::CalcDirection()
{
	float kMoveSpeed = 0.05f;
	Vector3 FlagPos = DestinationPosition_;
	Vector3 EnemyPos = GetWorldPosition();
	Vector3 F2E = VectorTransform::Subtruct(FlagPos, EnemyPos);
	F2E = VectorTransform::Normalize(F2E);

	// F2E.xに速度をかけないでmove()の処理に入ると
	// ラープっぽくなる
	// うまく使えばいい感じの作れるかも
	velocity_ = { F2E.x * kMoveSpeed, F2E.y, F2E.z * kMoveSpeed };
}


// エネミーの向きの計算
void NormalEnemy::CalcRotate()
{
	// 速度の取得
	Vector3 kVelocity = velocity_;

	// Y軸周り角度(θy)
	wt_.rotation.y = std::atan2(kVelocity.x, kVelocity.z);

	float velZ = std::sqrt((kVelocity.x * kVelocity.x) + (kVelocity.z * kVelocity.z));
	float height = -kVelocity.y;

	// X軸周り角度(θx)
	wt_.rotation.x = std::atan2(height, velZ);
}


// 目標地点までの距離
bool NormalEnemy::CalcDistance()
{
	Vector3 toDestination = {
		.x = wt_.translate.x - DestinationPosition_.x,
		.y = wt_.translate.y - DestinationPosition_.y,
		.z = wt_.translate.z - DestinationPosition_.z,
	};

	float length = VectorTransform::Length(toDestination);

	if (abs(length) < 1.0f) {
		return true;
	}

	return false;
}


// 縦の波移動
void NormalEnemy::CalcWaveVerticalMove()
{

}

#pragma endregion 


#pragma region  AttackPhase で使うメンバ関数

// 攻撃挙動処理
void NormalEnemy::MoveAttack()
{
	// 上昇処理
	AttackRise();

	// 降下処理
	AttackFalling();
}


// 攻撃の上昇処理
void NormalEnemy::AttackRise()
{
	// 上昇フラグが立っていなかったら早期リターン
	if (!isRiseFunc_) {
		return;
	}

	// 上昇目的座標の設定
	Vector3 risePos = {
		attackInitPos_.x,
		attackInitPos_.y + riseRate_,
		attackInitPos_.z,
	};

	// 上昇目的座標へのイージング
	if (riseNowFrame_ <= riseEndFrame_) {
		riseNowFrame_++;
	}
	wt_.translate.y =
		attackInitPos_.y + (risePos.y - attackInitPos_.y) * EaseOutQuart(float(riseNowFrame_) / float(riseEndFrame_));
	//wt_.translate.y += diffPosY_;

	// 終了したら上昇攻撃に入るフラグを折る
	if (riseNowFrame_ >= riseEndFrame_) {

		isFallFunc_ = true;
		isRiseFunc_ = false;

		// 降下の初期座標の取得
		// 上昇の終了時点での座標
		fallingInitPos_ = GetWorldPosition();

		// イージングに使う数値
		diffPosY_ = 0.0f;

		// 降下にかかる時間をセット
		SetFallFrame(0, 10);
	}
}


// 攻撃の落下処理
void NormalEnemy::AttackFalling()
{
	if (!isFallFunc_) {
		return;
	}

	// 下降目的座標の設定
	Vector3 risePos = {
		fallingInitPos_.x,
		attackInitPos_.y ,
		fallingInitPos_.z,
	};

	// 上昇目的座標へのイージング
	if (fallNowFrame_ <= fallEndFrame_) {
		fallNowFrame_++;
	}
	wt_.translate.y =
		fallingInitPos_.y + (risePos.y - fallingInitPos_.y) * EaseOutQuart(float(fallNowFrame_) / float(fallEndFrame_));

	// 終了１フレーム前に一瞬だけColliderIDをサイズを変える
	if (fallNowFrame_ == fallEndFrame_ - 1) {
		OBBCollider::SetID(enemyAttackID);
		SetDiffYSize(5.0f);
	}

	// 終了したら効果処理に入るフラグを折って、攻撃処理終了フラグを立てる
	if (fallNowFrame_ >= fallEndFrame_) {

		isRiseFunc_ = false;
		isFallFunc_ = false;
		isAttackMoveStart_ = false;
		isAttackMoveFinish_ = true;

		// 終了１フレーム前に一瞬だけColliderIDをサイズを戻す
		OBBCollider::SetID(enemyID);
		SetDiffYSize(1.0f);
	}
}


// 待機処理
bool NormalEnemy::WaitTime(uint32_t waitTime)
{
	// 最初の一回は引数で時間を設定
	if (!waitFlag_) {
		waitTimer_ = waitTime;
		waitFlag_ = true;
	}

	// 減算処理
	waitTimer_--;

	// 0以下で終了
	if (waitTimer_ <= 0) {

		// 時間を設定しなおして、フラグを折る
		waitTimer_ = 0;
		waitFlag_ = false;

		// trueを返す
		return true;
	}


	return false;
}


// イージング
float NormalEnemy::EaseOutQuart(float x)
{
	return 1.0f - std::pow(1.0f - x, 4.0f);
}


#pragma endregion 


#pragma region  DeadPhase で使うメンバ関数

// 死亡時処理
void NormalEnemy::KilledMove()
{
	// ライトを折る
	model_->UseLight(false);

	// y座標を加算
	wt_.translate.y += 0.06f;

	// ａｌｐｈａを減らして、透明にしていく
	color_.w -= 0.02f;

	// カラーの設定
	model_->SetColor(color_);
	ringModel_->SetColor(color_);


	// 透明になったら死亡フラグを立てる
	if (color_.w <= 0.0f) {
		isDead_ = true;
	}
}


// 自殺したときの移動処理
void NormalEnemy::SuicideMove()
{
	// ライトを折る
	model_->UseLight(false);

	// y座標を加算
	wt_.translate.y -= 0.03f;

	// ａｌｐｈａを減らして、透明にしていく
	color_.w -= 0.05f;

	// カラーの設定
	model_->SetColor(color_);

	// 透明になったら死亡フラグを立てる
	if (color_.w <= 0.0f) {
		isDead_ = true;
	}
}

#pragma endregion 


// OBBColliderのセッティング
void NormalEnemy::SettingCollider()
{
	this->size_ = {
		.x = 2.0f * wt_.scale.x,
		.y = 2.0f * wt_.scale.y,
		.z = 2.0f * wt_.scale.z,
	};

	size_.y = diffSizeY_;

	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->wt_.rotation);
}


// Colliderのビットのセッティング
void NormalEnemy::SettingColliderBit()
{
	OBBCollider::SetCollosionAttribute(kCollisionAttributeEnemy);
	OBBCollider::SetCollisionMask(kCollisionMaskEnemy);
	OBBCollider::SetID(enemyID);
}


// エネミーとエネミーが衝突したとき
void NormalEnemy::IsEnemyxEnemyHit()
{
	// エネミーと衝突したときに、
	// エネミーとの衝突のフラグがたっていなかったらフラグを立てる
	if (!hitEnemy_) {
		hitEnemy_ = true;
		hitEnemyTimer_ = 120;
		SettingDestinationPosition();
	}
	else if (hitEnemy_) {

		// タイマーを減らす
		hitEnemyTimer_--;

		// タイマーが０以下になったら
		if (hitEnemyTimer_ <= 0) {

			// フラグを折って、タイマーは０にしておく
			hitEnemy_ = false;
			hitEnemyTimer_ = 0;
		}
	}
}



