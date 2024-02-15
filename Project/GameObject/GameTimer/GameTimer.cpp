#include "GameTimer.h"

void GameTimer::Initialize()
{
	uint32_t Handle = TextureManager::LoadPngTexture("TimerTex.png");
	Vector2 texSize = TextureManager::GetTextureSize(Handle);
	
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState, {-texSize.x});
	sprite_->SetTexHandle(Handle);

	worldTransform_.Initialize();
	worldTransform_.scale = { float(Timer_ * 0.15f),0.5f,1.0f };
	worldTransform_.translate.x = 1280.0f - texSize.x;
	worldTransform_.translate.y = 64.0f;
	worldTransform_.UpdateMatrix();

	Handle = TextureManager::LoadPngTexture("TimerLogTex.png");

	SpriteLog_ = make_unique<Sprite>();
	SpriteLog_->Initialize(new SpriteBoxState);
	SpriteLog_->SetTexHandle(Handle);
	sprite_->SetColor(SpriteColor_);

	spriteLogWorldTransform_.Initialize();
	spriteLogWorldTransform_.scale = { 0.1f,0.1f,1.0f };
	spriteLogWorldTransform_.translate.x = 1280 - texSize.x * 3;
	spriteLogWorldTransform_.translate.y = 12.0f;
	spriteLogWorldTransform_.UpdateMatrix();

	
}

void GameTimer::Update()
{

	Timer_ = Timer_ - DeltaTimer();

	if (Timer_>30)
	{
		
		
		SpriteColor_ = { 0.0f,1.0f,0.0f,1.0f };
	}
	else if (Timer_ > 10)
	{

		SpriteColor_ = {1.0f, 1.0f, 0.0f, 1};
	}
	else if(Timer_ > 0)
	{
		
		SpriteColor_ = { 1.0f,0.0f,0.0f,1.0f };
	}

	if (Timer_ <= kTimer_)
	{
		isFinish_ = true;
	}

	sprite_->SetColor(SpriteColor_);
	worldTransform_.scale.x = float(Timer_ * 0.15f);
	spriteLogWorldTransform_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

void GameTimer::Draw(ViewProjection view)
{
	sprite_->Draw(worldTransform_, view);
	SpriteLog_->Draw(spriteLogWorldTransform_, view);
}

uint32_t GameTimer::DeltaTimer()
{
	Flame_++;
	if (Flame_/kFlame_ == 1.0f)
	{
		Flame_ = 0.0f;
		return 1;
	}
	else
	{
		return 0;
	}
}
