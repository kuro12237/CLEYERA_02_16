#include "TitleName.h"



void TitleName::Initialize()
{
	texHandle_ = TextureManager::LoadPngTexture("Title/TitleName.png");
	Vector2 titleTexSize = TextureManager::GetTextureSize(texHandle_);
	titleTexSize.x *= -0.5f;
	titleTexSize.y *= -0.5f;

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState, titleTexSize);
	sprite_->SetTexHandle(texHandle_);

	worldTransform_.Initialize();
	worldTransform_.translate = { 640.0f,270.0f,0.0f };
	worldTransform_.scale = { 0.6f,0.6f,0.6f };
}

void TitleName::Update()
{
#ifdef _DEBUG

	if (ImGui::TreeNode("Name"))
	{
		ImGui::DragFloat3("translate", &worldTransform_.translate.x, -1.0f, 1.0f);
		ImGui::TreePop();
	}
#endif // _DEBUG

	worldTransform_.UpdateMatrix();

}

void TitleName::Draw(ViewProjection view)
{
	sprite_->Draw(worldTransform_, view);
}
