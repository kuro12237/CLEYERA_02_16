#include "SpacePushSprite.h"

void SpacePushSprite::Initialize()
{
	worldTransform_.Initialize();
	uint32_t texhandle = TextureManager::LoadPngTexture("Push_A.png");
	Vector2 size = TextureManager::GetTextureSize(texhandle);
	size.x *= -0.5f;
	size.y *= -0.5f;
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState,size);
	sprite_->SetTexHandle(texhandle);
	worldTransform_.translate = { 640.0f,560.0f };

}

void SpacePushSprite::Update()
{
	timer_++;
	if (timer_>=kTimer_)
	{
		if (IsDraw_)
		{
			IsDraw_ = false;
		}
		else
		{
			IsDraw_ = true;
		}

		timer_ = 0;
	}
	worldTransform_.UpdateMatrix();
}

void SpacePushSprite::Draw(ViewProjection view)
{
	if (IsDraw_)
	{
		sprite_->Draw(worldTransform_, view);
	}
}
