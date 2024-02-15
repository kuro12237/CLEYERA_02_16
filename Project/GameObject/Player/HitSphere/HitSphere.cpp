#include "HitSphere.h"
#include "ModelManager.h"
#include <imgui.h>
#include <GameObject/Player/PlayerDirection.h>

HitSphere::HitSphere() {

}

void HitSphere::Initialize(uint32_t modelHandle) {

	//コンストラクタ
	model_ = std::make_unique<Game3dObject>();
	model_->Create();
	model_->SetModel(modelHandle);
	model_->UseLight(true);
	model_->SetlectModelPipeline(PHONG_MODEL);
	model_->SetShininess(30.0f);
	worldTransform_.Initialize();
	worldTransform_.scale = { radius_,radius_,radius_ };
	worldTransform_.rotation = { 0.0f,0.0f,0.0f };
	//初期はプレイヤーの所に
	worldTransform_.translate = VectorTransform::Add(playerPosition_, offset);;

}

Vector3 HitSphere::GetWorldPosition() {
	Vector3 result = {};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}



void HitSphere::Update() {


	const float length = 7.0f;
	//修正後のポジション
	Vector3 offsetedPosition = {};
	worldTransform_.rotation.y += 0.1f;
	//Y軸はずっと一緒にするべきである
	offsetedPosition.y = playerPosition_.y;
	if (playerDirection_ == Right) {
		offsetedPosition.x = playerPosition_.x + length;
		offsetedPosition.z = playerPosition_.z;
	}
	if (playerDirection_ == Left) {
		offsetedPosition.x = playerPosition_.x - length;
		offsetedPosition.z = playerPosition_.z;
	}
	if (playerDirection_ == Front) {
		offsetedPosition.x = playerPosition_.x;
		offsetedPosition.z = playerPosition_.z + length;
	}
	if (playerDirection_ == Back) {
		offsetedPosition.x = playerPosition_.x;
		offsetedPosition.z = playerPosition_.z - length;
	}

	

	//細かい処理が終わったらワールドトランスフォームに入れるよ
	worldTransform_.translate = offsetedPosition;
	worldTransform_.scale = { radius_,radius_,radius_ };

	worldTransform_.UpdateMatrix();




#ifdef _DEBUG 
if (ImGui::TreeNode("Hit")) {
	ImGui::SliderFloat3("Translate", &worldTransform_.translate.x, -10.0f, 10.0f);
	ImGui::InputFloat3("PlayerPosition", &playerPosition_.x);
	ImGui::InputFloat3("offsetedPosition", &offsetedPosition.x);
	ImGui::InputFloat("radius", &radius_);
	ImGui::TreePop();
	}
#endif

}

void HitSphere::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);

}

HitSphere::~HitSphere() {

}
