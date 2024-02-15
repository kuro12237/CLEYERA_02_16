#include "Hammer.h"
#include <GameObject/Player/PlayerDirection.h>


Hammer::Hammer() {

}

void Hammer::Initialize(uint32_t model) {
	//金属部分
	for (int i= 0; i < MODEL_AMOUNT_; i++) {
		model_[i] = std::make_unique<Game3dObject>();
		model_[i]->Create();
		model_[0]->UseLight(true);
		model_[0]->SetlectModelPipeline(PHONG_MODEL);
		model_[0]->SetModel(model);
	
		//ワールドトランスフォームの初期化
		worldTransform_[i].Initialize();

#pragma region ワールドトランスフォーム
		//SRT
		const float SCALE = 3.0f;
		worldTransform_[i].scale = { SCALE,SCALE,SCALE };
		worldTransform_[i].rotation = { 0.0f,0.0f,0.0f };
		worldTransform_[i].translate = { 0.0f,0.0f,0.0f };

#pragma endregion

	}
	ModelManager::ModelLoadNormalMap();
	uint32_t rotatedHammerModel = ModelManager::LoadObjectFile("RotatedPlayerHammer");
	model_[1]->UseLight(true);
	model_[1]->SetlectModelPipeline(PHONG_MODEL);
	model_[1]->SetModel(rotatedHammerModel);
	
	
	

	


}


//ボタンが押されたとき
void Hammer::TriggerAttack() {

	//Z方向に回転
	float rotateX = 0.0f;
	float rotateZ = 0.0f;

	//そういえば回転は反時計回りだったね
	//右
	if (playerDirection_ == Right) {
		rotateZ = -ROTATE_AMOUNT_;
		rotateHammerHand_.z = -ROTATE_AMOUNT_;
		if (worldTransform_[0].rotation.z < -(float(std::numbers::pi)) / 2.0f) {
			worldTransform_[0].rotation.z = -(float(std::numbers::pi)) / 2.0f;
			//ハンマーの持つ手も回転
			rotateHammerHand_.z= -(float(std::numbers::pi)) / 2.0f;
			isPreAttack_ = false;
			isAttack_ = true;
		}

	}

	//左
	if (playerDirection_ == Left) {
		rotateZ = +ROTATE_AMOUNT_;

		if (worldTransform_[0].rotation.z > (float(std::numbers::pi)) / 2.0f) {
			worldTransform_[0].rotation.z = (float(std::numbers::pi)) / 2.0f;
			isPreAttack_ = false;
			isAttack_ = true;
		}
	}


	//ジンバルロック発生！！
	//使い方マスターできていないから応急処置としてモデル2つ用意する

	//前
	if (playerDirection_ == Front) {
		rotateX = +ROTATE_AMOUNT_;
		if (worldTransform_[1].rotation.x > (float(std::numbers::pi)) / 2.0f) {
			worldTransform_[1].rotation.x = (float(std::numbers::pi)) / 2.0f;
			isPreAttack_ = false;
			isAttack_ = true;
		}
	}

	//後ろ
	if (playerDirection_ == Back) {
		rotateX = -ROTATE_AMOUNT_;
		if (worldTransform_[1].rotation.x < -(float(std::numbers::pi)) / 2.0f) {
			worldTransform_[1].rotation.x = -(float(std::numbers::pi)) / 2.0f;
			isPreAttack_ = false;
			isAttack_ = true;
		}
	}

	worldTransform_[0].rotation.z += rotateZ;
	worldTransform_[1].rotation.x += rotateX;
	//ハンマーが使う角度
	//float thetaV = 0.0f;
	//hitSpherePosition_

#ifdef _DEBUG 

	if (ImGui::TreeNode("HammerRotate")) {
		ImGui::InputFloat("rotateZ", &rotateZ);
		ImGui::InputFloat("rotateX", &rotateX);
		ImGui::TreePop();
	}
#endif
	//ハンマーが90度時計回りしたら攻撃当たるようになる


	/*if (worldTransform_.rotation.z < -(float(std::numbers::pi)) / 2.0f||
		worldTransform_.rotation.z > (float(std::numbers::pi)) / 2.0f) {
		isPreAttack_ = false;
		isAttack_ = true;
	}*/
}


//リセット
void Hammer::Reset() {
	//左右
	worldTransform_[0].rotation.z += ROTATE_AMOUNT_;
	//右
	if (worldTransform_[0].rotation.z > INITIAL_ROTATE_) {
		worldTransform_[0].rotation.z = INITIAL_ROTATE_;
		//ハンマーの持つ手も回転
 		rotateHammerHand_.z = 0.0f;
		isResetRotate_ = false;
	}
	//左
	if (worldTransform_[0].rotation.z < INITIAL_ROTATE_) {
		worldTransform_[0].rotation.z = INITIAL_ROTATE_;
		rotateHammerHand_.z = 0.0f;
		isResetRotate_ = false;
	}

	//前後
	worldTransform_[1].rotation.x += ROTATE_AMOUNT_;
	//右
	if (worldTransform_[1].rotation.x > INITIAL_ROTATE_) {
		worldTransform_[1].rotation.x = INITIAL_ROTATE_;
		rotateHammerHand_.z = 0.0f;
		isResetRotate_ = false;
	}
	//左
	if (worldTransform_[1].rotation.x < INITIAL_ROTATE_) {
		worldTransform_[1].rotation.x = INITIAL_ROTATE_;
		rotateHammerHand_.z = 0.0f;
		isResetRotate_ = false;
	}

}


Vector3 Hammer::GetWorldPosition() {

	Vector3 result = {};
	result.x = worldTransform_[0].matWorld.m[3][0];
	result.y = worldTransform_[0].matWorld.m[3][1];
	result.z = worldTransform_[0].matWorld.m[3][2];

	return result;
}


void Hammer::Update() {

#ifdef _DEBUG 
	if (ImGui::TreeNode("Hammer")) {
		ImGui::SliderFloat("Rotation", &worldTransform_[1].rotation.x, -(float(std::numbers::pi)) / 2.0f, (float(std::numbers::pi)) / 2.0f);

		ImGui::Checkbox("isResetRotate", &isResetRotate_);
		ImGui::TreePop();
	}

#endif
	for (int i = 0; i < MODEL_AMOUNT_; i++) {

#pragma region プレイヤーの向いている方向に対応してハンマーの向きも変わる

		//右
		if (playerDirection_ == Right) {
			worldTransform_[0].rotation.y = 0.0f;
		}
		//左
		if (playerDirection_ == Left) {
			worldTransform_[0].rotation.y = float(std::numbers::pi);
		}
		////前
		//if (playerDirection_ == Front) {
		//	worldTransform_[0].rotation.y = float(std::numbers::pi) / 2.0f;

		//}
		////後ろ
		//if (playerDirection_ == Back) {
		//	worldTransform_[0].rotation.y = 3.0f * float(std::numbers::pi) / 2.0f;
		//}

#pragma endregion

		//ボタンが押されたときハンマーが回転する
		if (isPreAttack_ == true) {
			TriggerAttack();
		}

		//回転した後のままで攻撃
		if (isAttack_ == true) {
			//右
			if (worldTransform_[0].rotation.z < -(float(std::numbers::pi)) / 2.0f) {
				worldTransform_[0].rotation.z = -(float(std::numbers::pi)) / 2.0f;
				rotateHammerHand_.z = -(float(std::numbers::pi)) / 2.0f;
			}
			if (worldTransform_[0].rotation.z > (float(std::numbers::pi)) / 2.0f) {
				worldTransform_[0].rotation.z = (float(std::numbers::pi)) / 2.0f;
			}

			//前後
			if (worldTransform_[1].rotation.x < -(float(std::numbers::pi)) / 2.0f) {
				worldTransform_[1].rotation.x = -(float(std::numbers::pi)) / 2.0f;
			}
			if (worldTransform_[1].rotation.x > (float(std::numbers::pi)) / 2.0f) {
				worldTransform_[1].rotation.x = (float(std::numbers::pi)) / 2.0f;
			}



		}
		//加速度

		//リセット
		if (isResetRotate_ == true) {

			Reset();
		}

		//ワールドトランスフォームの更新
		worldTransform_[i].UpdateMatrix();
	}
}

void Hammer::Draw(ViewProjection viewProjection) {
	//左右
	if (playerDirection_ == Right || playerDirection_ == Left) {
		model_[0]->Draw(worldTransform_[0], viewProjection);
	}
	//前後
	if (playerDirection_ == Front || playerDirection_ == Back) {
		model_[1]->Draw(worldTransform_[1], viewProjection);
	}
}

Hammer::~Hammer() {

}
