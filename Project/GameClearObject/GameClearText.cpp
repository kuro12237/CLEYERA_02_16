#include "GameClearText.h"

void GameClearText::Initialize()
{
	uint32_t texHandle = TextureManager::LoadPngTexture("GameClear.png");
	Vector2 texSize = TextureManager::GetTextureSize(texHandle);
	texSize.x *= -0.5f;
	texSize.y *= -0.5f;

	worldTransform_.Initialize();
	worldTransform_.translate = { 640.0f,320.0f };

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState,texSize);
	sprite_->SetTexHandle(texHandle);
}

void GameClearText::Update()
{
	worldTransform_.UpdateMatrix();
}

void GameClearText::Draw(ViewProjection view)
{
	sprite_->Draw(worldTransform_, view);
}
