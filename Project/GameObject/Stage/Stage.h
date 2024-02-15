#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Game3dObject.h>

#include <memory>
class Stage{
private:
	static const int MODEL_AMOUNT_ = 3;


public:
	//コンストラクタ
	Stage();

	//初期化
	void Initialize(uint32_t stageModel[MODEL_AMOUNT_]);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);

	//デストラクタ
	~Stage();


private:
	
	//ワールドトランスフォーム
	WorldTransform worldTransform_[MODEL_AMOUNT_] = {};

	//モデル
	std::unique_ptr<Game3dObject> model_[MODEL_AMOUNT_] = { nullptr };


};

