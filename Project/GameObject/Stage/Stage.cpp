#include "Stage.h"

#include "Input.h"
#include "VectorTransform.h"
//コンストラクタ
Stage::Stage() {

}

//初期化
void Stage::Initialize(uint32_t stageModel[MODEL_AMOUNT_]) {

	for (int i = 0; i < MODEL_AMOUNT_; i++) {
		//モデルを作る
		model_[i] = std::make_unique<Game3dObject>();
		model_[i]->Create();
		model_[i]->SetModel(stageModel[i]);

		//ワールドトランスフォームの初期化
		worldTransform_[i].Initialize();
	}
	
	

#pragma region ワールドトランスフォーム
	//SRT
	const float SCALE = 1.0f;
	//Box1
	worldTransform_[0].scale = { SCALE,SCALE,SCALE };
	worldTransform_[0].rotation = { 0.0f,0.0f,0.0f };
	worldTransform_[0].translate = { 0.0f,0.0f,0.0f };

	//Box2
	worldTransform_[1].scale = { SCALE,SCALE,SCALE };
	worldTransform_[1].rotation = { 0.0f,0.0f,0.0f };
	worldTransform_[1].translate = { 0.0f,0.0f,0.0f };

	//Box3
	worldTransform_[2].scale = { SCALE,SCALE,SCALE };
	worldTransform_[2].rotation = { 0.0f,0.0f,0.0f };
	worldTransform_[2].translate = { 0.0f,0.0f,0.0f };

#pragma endregion


}

//更新
void Stage::Update() {
	//ワールドトランスフォームの更新
	for (int i = 0; i < MODEL_AMOUNT_; i++) {
		worldTransform_[i].UpdateMatrix();
	}
}

//描画
void Stage::Draw(ViewProjection viewProjection) {
	//モデルの描画
	for (int i = 0; i < MODEL_AMOUNT_; i++) {
		model_[i]->Draw(worldTransform_[i], viewProjection);
	}
}

//デストラクタ
Stage::~Stage() {


}
