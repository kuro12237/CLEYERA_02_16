#include "Sun.h"

void Sun::Initialize(Vector3 pos,float intencity)
{
	LeftLight_.decay = 0.5f;
	LeftLight_.position = pos;
	LeftLight_.radious = 1280.0f;
	LeftLight_.intencity = intencity;

	uint32_t modelHandle = ModelManager::LoadObjectFile("testSphere");
	worldTransform_.Initialize();
	worldTransform_.scale = { 0.5f,0.5f,0.5f };
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle);
	
}

void Sun::Update()
{
#ifdef _DEBUG

	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("Pos", &LeftLight_.position.x);
		ImGui::DragFloat("dacey", &LeftLight_.decay);
		ImGui::DragFloat("intencity", &LeftLight_.intencity);
		ImGui::TreePop();
	}

#endif // _DEBUG

	worldTransform_.translate = LeftLight_.position;
	worldTransform_.UpdateMatrix();
	LightingManager::AddList(LeftLight_);
}

void Sun::Draw(ViewProjection view)
{
#ifdef _DEBUG
	gameObject_->Draw(worldTransform_, view);
#endif // _DEBUG
}

void Sun::SetPos(Vector3 pos)
{
	if (SunManager::GetPlayerFlag())
	{
		LeftLight_.position.x = pos.x;
		LeftLight_.position.y = pos.y + 5.0f;
		LeftLight_.position.z = pos.z;
	};
}
