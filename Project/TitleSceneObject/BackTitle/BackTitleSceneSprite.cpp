#include "BackTitleSceneSprite.h"

void BackTitleSceneSprite::Initlaize()
{
	texHandle_ = TextureManager::LoadPngTexture("Title/BackTitleScene.png");
	Vector2 size = TextureManager::GetTextureSize(texHandle_);
	size.x *= -0.5f;
	size.y *= -0.5f;
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState,size);
	sprite_->SetTexHandle(texHandle_);
	worldTransform_.Initialize();
	worldTransform_.translate = { 640.0f,360.0f };
}

void BackTitleSceneSprite::Update()
{


	worldTransform_.UpdateMatrix();
}

void BackTitleSceneSprite::Draw(ViewProjection view)
{
	sprite_->Draw(worldTransform_, view);
}
