#include "GameOverSprite.h"

void GameOverSprite::Initialize()
{
	uint32_t texHandle = TextureManager::LoadPngTexture("GameOver.png");
	Vector2 texSize = TextureManager::GetTextureSize(texHandle);
	texSize.x *= -0.5f;
	texSize.y *= -0.5f;

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState,texSize);
	sprite_->SetTexHandle(texHandle);

	worldTransform_.Initialize();
	worldTransform_.translate = { 640.0f,320.0f };
}

void GameOverSprite::Update()
{
	worldTransform_.UpdateMatrix();
}

void GameOverSprite::Draw(ViewProjection view)
{
	sprite_->Draw(worldTransform_, view);
}
