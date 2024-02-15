#include "Clock.h"

Clock* Clock::GetInstance()
{
	static Clock instance;
	return &instance;
}

void Clock::Initialize()
{
	Clock::GetInstance()->needleHandle2_ = ModelManager::LoadObjectFile("needle2");
	Clock::GetInstance()->needleObj2 = make_unique<Game3dObject>();
	Clock::GetInstance()->needleObj2->Create();
	Clock::GetInstance()->needleObj2->SetModel(Clock::GetInstance()->needleHandle2_);
	Clock::GetInstance()->needleObj2->UseLight(true);
	Clock::GetInstance()->needlePos2_.Initialize();
	Clock::GetInstance()->needlePos2_.scale = { 2.0f,2.0f,2.0f };
	Clock::GetInstance()->needlePos2_.rotation = { 0.0f,0.0f,0.0f };
	Clock::GetInstance()->needlePos2_.translate = { 0.0f,0.0f,118.0f };
	//
	Clock::GetInstance()->needleHandle_ = ModelManager::LoadObjectFile("needle");
	Clock::GetInstance()->needleObj = make_unique<Game3dObject>();
	Clock::GetInstance()->needleObj->Create();
	Clock::GetInstance()->needleObj->SetModel(Clock::GetInstance()->needleHandle_);
	Clock::GetInstance()->needleObj->UseLight(true);
	Clock::GetInstance()->needlePos_.Initialize();
	Clock::GetInstance()->needlePos_.scale = { 2.0f,2.0f,2.0f };
	Clock::GetInstance()->needlePos_.rotation = { 0.0f,0.0f,0.0f };
	Clock::GetInstance()->needlePos_.translate = { 0.0f,0.0f,118.0f };
	//
	Clock::GetInstance()->modelHandle_ = ModelManager::LoadObjectFile("time");
	Clock::GetInstance()->timeObj = make_unique<Game3dObject>();
	Clock::GetInstance()->timeObj->Create();
	Clock::GetInstance()->timeObj->SetModel(Clock::GetInstance()->modelHandle_);
	Clock::GetInstance()->timeObj->UseLight(true);
	Clock::GetInstance()->timePos_.Initialize();
	Clock::GetInstance()->timePos_.scale={ 2.0f,2.0f,2.0f };
	Clock::GetInstance()->timePos_.rotation = { 0.0f,0.0f,0.0f };
	Clock::GetInstance()->timePos_.translate = { 0.0f,0.0f,120.0f };
	Clock::GetInstance()->color_ ={ 0.5f, 0.5f, 0.5f, 1.0f };
}

void Clock::Update()
{
	Clock::GetInstance()->needlePos2_.rotation.z -= 0.01f;
	Clock::GetInstance()->needlePos_.rotation.z -= 0.05f;
#ifdef _DEBUG
	ImGui::Begin("Clock");
	ImGui::ColorPicker4("color", &Clock::GetInstance()->color_.x);
	ImGui::DragFloat3("translate", &Clock::GetInstance()->needlePos_.translate.x);
	ImGui::End();
#endif // _DEBUG
	SettingMaterial_Param();
	GetInstance()->needlePos2_.UpdateMatrix();
	GetInstance()->needlePos_.UpdateMatrix();
	GetInstance()->timePos_.UpdateMatrix();
}

void Clock::Draw(ViewProjection view)
{
	Clock::GetInstance()->needleObj2->Draw(Clock::GetInstance()->needlePos2_, view);
	Clock::GetInstance()->needleObj->Draw(Clock::GetInstance()->needlePos_, view);
	Clock::GetInstance()->timeObj->Draw(Clock::GetInstance()->timePos_, view);
}

void Clock::SettingMaterial_Param()
{
	Clock::GetInstance()->needleObj2->SetColor(Clock::GetInstance()->color2_);
	Clock::GetInstance()->needleObj->SetColor(Clock::GetInstance()->color2_);
	Clock::GetInstance()->timeObj->SetColor(Clock::GetInstance()->color_);
	Clock::GetInstance()->timeObj->SetRoughness(Clock::GetInstance()->roughness_);
	Clock::GetInstance()->timeObj->SetSpecular(Clock::GetInstance()->Specular_);
	Clock::GetInstance()->timeObj->SetMetalness(Clock::GetInstance()->metalness_);

}