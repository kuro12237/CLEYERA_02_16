#include "Flag.h"



void Flag::Initialize(uint32_t modelHD, Vector3 position) {

	object_ = make_unique<Game3dObject>();
	object_->Create();
	object_->SetModel(modelHD);

	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.scale = { 0.5f, 0.5f, 0.5f };
	size_ = { 2.0f, 2.0f, 1.5f };
	worldTransform_.UpdateMatrix();

	SettingColliderBit();
}


void Flag::Update(Vector3 position) {

	SettingOBB();
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();
}


void Flag::Draw(ViewProjection view) {

	object_->Draw(worldTransform_, view);
}


void Flag::OnCollision(uint32_t id) {

	id;
}


Vector3 Flag::GetWorldPosition() {

	// ワールド座標を入れる変数
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}


void Flag::SettingOBB() {

	this->size_ = {
		.x = 1.0f * worldTransform_.scale.x,
		.y = 1.0f * worldTransform_.scale.y,
		.z = 0.2f * worldTransform_.scale.z,
	};

	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTransform_.rotation);

}


void Flag::SettingColliderBit() {

	OBBCollider::SetCollosionAttribute(kCollisionAttributeFlag);
	OBBCollider::SetCollisionMask(kCollisionMaskFlag);
	OBBCollider::SetID(flagID);
}