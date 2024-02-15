#include "GameStartCount.h"

void GameStartCount::Initialize()
{
	texHandle_ = TextureManager::LoadPngTexture("GameStartCount.png");
	
	Vector2 texSize = TextureManager::GetTextureSize(texHandle_);

	texSize.x *= 0.25f;
	texSize.y *= 0.25f;

	int32_t x = 0;
	int32_t y = 0;

	for (int c = 5; c > 1; c--)
	{
		CountNumber_[c] = { 
			{ 0.0f + x * 0.25f , 0.0f + y * 0.25f },
			{ 0.0f + x * 0.25f, 0.25f + y  * 0.25f},
			{ 0.25f + x * 0.25f , 0.0f + y * 0.25f},
			{ 0.25f + x * 0.25f , 0.25f + y * 0.25f }
		};
		x++;
	}
	CountNumber_[0] = {
		{ 0.0f, 0.25f},
			{ 0.0f, 0.5f},
			{ 0.5f, 0.25f},
			{ 0.5f, 0.5f}
	};


	Vector2 posTex = { texSize.x * -0.5f,texSize.y * -0.5f };

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState,{},posTex);
	sprite_->SetSrc(
		CountNumber_[4].Lt,
		CountNumber_[4].Lb,
		CountNumber_[4].Rt,
		CountNumber_[4].Rb
	);
	sprite_->SetTexHandle(texHandle_);

	worldTransform_.Initialize();
	worldTransform_.scale = { 0.25f,0.25f,0.25f };
	worldTransform_.translate = { 640.0f - 64.0f,144.0f };
	worldTransform_.UpdateMatrix();

	countSE_ = Audio::GetInstance();
	countSEHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Ready/Count.wav");

	startSE_ = Audio::GetInstance();
	startSEHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Ready/Start.wav");

}

void GameStartCount::Update()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("GameStartcount"))
	{
		ImGui::Text("%d", timeCount_);
		ImGui::TreePop();
	}
#endif // _DEBUG

	int32_t prevTimeCount = timeCount_;
	

	if (timeCount_ > 0)
	{
		flameTime_++;
		timeCount_ -= DeltaTimer();

		sprite_->SetSrc(
			CountNumber_[timeCount_].Lt,
			CountNumber_[timeCount_].Lb, 
			CountNumber_[timeCount_].Rt,
			CountNumber_[timeCount_].Rb
			);


	}
	else if (timeCount_==1) {
		startSE_->PlayWave(startSEHandle_, false);
	}
	//0になったらカウント終了
	else if (timeCount_ == 0)
	{
		
		
		
		isCountFinishFlag_ = true;
	}

	ColorUpdate(prevTimeCount);

	worldTransform_.UpdateMatrix();
}

void GameStartCount::Draw(ViewProjection view)
{
	sprite_->Draw(worldTransform_, view);
}

int32_t GameStartCount::DeltaTimer()
{
	if (flameTime_ %kFlameMaxTimer_ == 0)
	{
		countSE_->PlayWave(countSEHandle_, false);
		flameTime_ = 1;
		return 1;
	}
	return 0;
}

void GameStartCount::ColorUpdate(int32_t prevTime)
{
	const float kColorSubtractSpeed = 0.02f;
	if (timeCount_ == prevTime)
	{
		color_.w -= kColorSubtractSpeed;
	}
	else if (timeCount_ != prevTime)
	{
		color_ = { 1.0f,1.0f,1.0f,1.0f };
	}
	sprite_->SetColor(color_);
}
