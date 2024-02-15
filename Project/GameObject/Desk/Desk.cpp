#include "Desk.h"

Desk* Desk::GetInstance()
{
	static Desk instance;
	return &instance;
}

void Desk::Initialize()
{
	Desk::GetInstance()->modelHandle_ = ModelManager::LoadObjectFile("desk");
	Desk::GetInstance()->DeskObj = make_unique<Game3dObject>();
	Desk::GetInstance()->DeskObj->Create();
	Desk::GetInstance()->DeskObj->SetModel(Desk::GetInstance()->modelHandle_);
	Desk::GetInstance()->DeskObj->UseLight(true);
	Desk::GetInstance()->DeskPos_.Initialize();
	Desk::GetInstance()->DeskPos_.scale = { 0.8f,0.8f,0.8f };
	Desk::GetInstance()->DeskPos_.rotation = { 0.0f,0.0f,0.0f };
	Desk::GetInstance()->DeskPos_.translate = { 63.0f,-24.0f,71.0f };
	Desk::GetInstance()->color_ = { 0.1f,1.0f,1.0f,1.0f };


	Desk::GetInstance()->modelHandle2_ = ModelManager::LoadObjectFile("desk");
	Desk::GetInstance()->DeskObj2 = make_unique<Game3dObject>();
	Desk::GetInstance()->DeskObj2->Create();
	Desk::GetInstance()->DeskObj2->SetModel(Desk::GetInstance()->modelHandle2_);
	Desk::GetInstance()->DeskObj2->UseLight(true);
	Desk::GetInstance()->DeskPos2_.Initialize();
	Desk::GetInstance()->DeskPos2_.scale = { 0.5f,0.5f,0.5f };
	Desk::GetInstance()->DeskPos2_.rotation = { 0.0f,9.0f,0.0f };
	Desk::GetInstance()->DeskPos2_.translate = { -63.0f,-20.0f,-71.0f };
}

void Desk::Update()
{
#ifdef _DEBUG
	ImGui::Begin("Desk");
	ImGui::ColorPicker4("color", &Desk::GetInstance()->color_.x);
	ImGui::DragFloat3("translate", &Desk::GetInstance()->DeskPos_.translate.x);
	ImGui::DragFloat3("rotation", &Desk::GetInstance()->DeskPos_.rotation.x);
	ImGui::End();
#endif // _DEBUG
	GetInstance()->DeskPos_.UpdateMatrix();
	GetInstance()->DeskPos2_.UpdateMatrix();
}

void Desk::Draw(ViewProjection view)
{
	Desk::GetInstance()->DeskObj->Draw(Desk::GetInstance()->DeskPos_, view);
	Desk::GetInstance()->DeskObj2->Draw(Desk::GetInstance()->DeskPos2_, view);
}

void Desk::SettingMaterial_Param()
{
	Desk::GetInstance()->DeskObj->SetColor(Desk::GetInstance()->color_);
	Desk::GetInstance()->DeskObj->SetRoughness(Desk::GetInstance()->roughness_);
	Desk::GetInstance()->DeskObj->SetSpecular(Desk::GetInstance()->Specular_);
	Desk::GetInstance()->DeskObj->SetMetalness(Desk::GetInstance()->metalness_);
}
