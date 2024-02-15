#include "Ground.h"

void Ground::Initialize(Vector3 pos, Vector3 size, Vector3 spritePos, uint32_t heel ,uint32_t damege)
{
	ModelManager::ModelLoadNormalMap();
	ModelManager::ModelUseSubsurface();
	modelHandle_ = ModelManager::LoadObjectFile("Ground");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->UseLight(true);
	gameObject_->SetModel(modelHandle_);
	gameObject_->SetlectModelPipeline(PHONG_SUBSURFACE_MODEL);
	worldTrabsform.Initialize();
	Scale_ = size;
	worldTrabsform.scale = Scale_;
	worldTrabsform.translate = pos;
	worldTrabsform.UpdateMatrix();
	SettingColliderBit();

	// ダメージ
	heel_ = heel;
	damage_ = damege;

	// 体力スプライト
	HPTexHD_ = TextureManager::LoadPngTexture("Ground/GroundHP.png");
	spriteHP_ = make_unique<Sprite>();
	spriteHP_->Initialize(new SpriteBoxState());
	spriteHP_->SetTexHandle(HPTexHD_);
	spriteWT_.Initialize();
	spriteWT_.translate = { spritePos.x, spritePos.y, 0.0f };
	spriteWT_.scale.y = 0.5f;
	spColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 床のレベルとHP
	Level_ = 2;
	HP_ = 20;
	isHit_ = false;

	// ラベルの読み込み
	labelG_ = TextureManager::LoadPngTexture("Lavel/good.png");
	labelM_ = TextureManager::LoadPngTexture("Lavel/not.png");
	labelB_ = TextureManager::LoadPngTexture("Lavel/over.png");

	labelSp_ = make_unique<Sprite>();
	labelSp_->Initialize(new SpriteBoxState());
	labelSp_->SetTexHandle(labelM_);
	labelWt_.Initialize();
	labelWt_.translate = { spritePos.x, spritePos.y, 0.0f };
	labelWt_.scale = { 0.5f, 0.5f, 0.5f };
}

void Ground::Update()
{
	// OBBColliderのセッティング
	SettingOBB();

	// レベルをHPの数値を基準に決める
	CalcLevel();

	// HP用のスプライトの更新処理
	SpriteHPUpdate();

	// ラベルスプライトの更新処理
	LavelUpdate();


#ifdef _DEBUG
	/*if (ImGui::TreeNode("Ground"))
	{
		ImGui::DragFloat("scale.X", &Scale_.x, 0.1f, 1.0f, 100.0f);
		ImGui::DragFloat("scale.Z", &Scale_.z, 0.1f, 1.0f, 100.0f);
		ImGui::SliderFloat3("Translate", &translate_.x, -3.5f, 3.5f);
		ImGui::TreePop();
	}*/
#endif // _DEBUG

	worldTrabsform.UpdateMatrix();
}

void Ground::DrawF2D(ViewProjection view)
{
	spriteHP_->Draw(spriteWT_, view);

	labelSp_->Draw(labelWt_, view);
}
void Ground::Draw3D(ViewProjection view)
{
	gameObject_->Draw(worldTrabsform, view);
}

void Ground::OnCollision(uint32_t id)
{
	if (id == enemyID) {
		isHit_ = true;
		HP_ += heel_;
		return;
	}
	else if (id == enemyAttackID) {
		isHit_ = true;
		HP_ -= damage_;
		return;
	}
}

Vector3 Ground::GetWorldPosition()
{
	Vector3 worldPos = {
		worldTrabsform.matWorld.m[3][0],
		worldTrabsform.matWorld.m[3][1],
		worldTrabsform.matWorld.m[3][2],
	};
	return worldPos;
}


// OBBColliderのセッティング
void Ground::SettingOBB()
{
	this->size_ = {
		.x = 2.0f * worldTrabsform.scale.x,
		.y = 2.0f * worldTrabsform.scale.y,
		.z = 2.0f * worldTrabsform.scale.z,
	};

	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTrabsform.rotation);
	//CollisionManager::ColliderOBBPushBack(this);
}


// Colliderのビットのセッティング
void Ground::SettingColliderBit()
{
	OBBCollider::SetCollosionAttribute(kCollisionAttributeGround);
	OBBCollider::SetCollisionMask(kCollisionMaskGround);
	OBBCollider::SetID(groundID);
}


// HPによってレベルが変わる
void Ground::CalcLevel()
{
	if (HP_ < 10) {
		Level_ = 1;
		spriteWT_.scale.x = 0.2f;
		spColor_ = ConvertColor(spColor_, { 204.0f, 0.0f, 0.0f });
		color_ = ConvertColor(color_, { 204.0f, 0.0f, 0.0f });
	}
	else if (HP_ >= 10 && HP_ < 20) {
		Level_ = 2;
		spriteWT_.scale.x = 1.0f;
		spColor_ = ConvertColor(spColor_, { 204.0f, 51.0f, 51.0f });
		color_ = ConvertColor(color_, { 204.0f, 51.0f, 51.0f });
	}
	else if (HP_ >= 20 && HP_ < 30) {
		Level_ = 3;
		spriteWT_.scale.x = 2.0f;
		spColor_ = ConvertColor(spColor_, { 255.0f, 255.0f, 127.0f });
		color_ = ConvertColor(color_, { 255.0f, 255.0f, 127.0f });
	}
	else if (HP_ >= 30 && HP_ < 40) {
		Level_ = 4;
		spriteWT_.scale.x = 3.0f;
		spColor_ = ConvertColor(spColor_, { 153.0f, 255.0f, 153.0f });
		color_ = ConvertColor(color_, { 153.0f, 255.0f, 153.0f });
	}
	else if (HP_ >= 40 && HP_ < 50) {
		Level_ = 5;
		spriteWT_.scale.x = 4.0f;
		spColor_ = ConvertColor(spColor_, { 51.0f, 255.0f, 102.0f });
		color_ = ConvertColor(color_, { 51.0f, 255.0f, 102.0f });
	}
	else if (HP_ >= 50 && HP_ < 60) {
		Level_ = 6;
		spriteWT_.scale.x = 5.0f;
		spColor_ = ConvertColor(spColor_, { 51.0f, 255.0f, 102.0f });
		color_ = ConvertColor(color_, { 51.0f, 255.0f, 102.0f });
	}
	else if (HP_ >= 60 && HP_ < 70) {
		Level_ = 7;
		spriteWT_.scale.x = 6.0f;
		spColor_ = ConvertColor(spColor_, { 51.0f, 255.0f, 102.0f });
		color_ = ConvertColor(color_, { 51.0f, 255.0f, 102.0f });
	}
	else if (HP_ >= 70 && HP_ < 80) {
		Level_ = 8;
		spriteWT_.scale.x = 7.0f;
		spColor_ = ConvertColor(spColor_, { 255.0f, 255.0f, 127.0f });
		color_ = ConvertColor(color_, { 255.0f, 255.0f, 127.0f });
	}
	else if (HP_ >= 80 && HP_ < 90) {
		Level_ = 9;
		spriteWT_.scale.x = 7.0f;
		spColor_ = ConvertColor(spColor_, { 204.0f, 51.0f, 51.0f });
		color_ = ConvertColor(color_, { 204.0f, 51.0f, 51.0f });
	}
	else if (HP_ >= 90 && HP_ < 100) {
		Level_ = 10;
		spriteWT_.scale.x = 7.0f;
		spColor_ = ConvertColor(spColor_, { 204.0f, 0.0f, 0.0f });
		color_ = ConvertColor(color_, { 204.0f, 0.0f, 0.0f });
	}

	if (HP_ <= 0) {
		HP_ = 0;
	}
	if (HP_ >= 100) {
		HP_ = 100;
	}


	gameObject_->SetColor(color_);
	spriteHP_->SetColor(spColor_);
}


// HP用スプライトの更新処理
void Ground::SpriteHPUpdate()
{
	spriteWT_.UpdateMatrix();

}


// 色の変更
Vector4 Ground::ConvertColor(Vector4 old_Color, Vector3 new_Color)
{
	Vector4 resultColor = {
		.x = new_Color.x / 256.0f,
		.y = new_Color.y / 256.0f,
		.z = new_Color.z / 256.0f,
		.w = old_Color.w,
	};

	return resultColor;
}

void Ground::LavelUpdate()
{
	labelWt_.UpdateMatrix();

	if (Level_ >= 1 && Level_ <= 4) {
		labelSp_->SetTexHandle(labelM_);
	}
	else if (Level_ >= 5 && Level_ <= 7) {
		labelSp_->SetTexHandle(labelG_);
	}
	else if (Level_ >= 8 && Level_ <= 10) {
		labelSp_->SetTexHandle(labelB_);
	}

	if (Level_ >= 1 && Level_ <= 2 || Level_ >= 8 && Level_ <= 10) {
		state_ = Bad;
	}
	else if (Level_ >= 3 && Level_ <= 4) {
		state_ = More;
	}
	else if (Level_ >= 5 && Level_ <= 7) {
		state_ = Good;
	}
}
