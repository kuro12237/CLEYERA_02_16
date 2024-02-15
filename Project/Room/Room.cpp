#include "Room.h"

Room *Room::GetInstance()
{
	static Room instance;
	return &instance;
}

void Room::Initialize()
{
	if (!Room::GetInstance()->InitlializeLock_)
	{
		ModelManager::ModelLoadNormalMap();
		Room::GetInstance()->modelHandle_ = ModelManager::LoadObjectFile("Room");
		Room::GetInstance()->gameObject_ = make_unique<Game3dObject>();
		Room::GetInstance()->gameObject_->Create();
		Room::GetInstance()->gameObject_->SetModel(Room::GetInstance()->modelHandle_);
		Room::GetInstance()->gameObject_->UseLight(true);
		Room::GetInstance()->gameObject_->SetlectModelPipeline(PHONG_NORMAL_MODEL);


		Room::GetInstance()->worldTransofrm_.Initialize();
		Room::GetInstance()->InitlializeLock_ = true;

		//Room::GetInstance()->worldTransofrm_.scale = { 0.5f,0.5f,0.5f };
	}
}

void Room::Update()
{
	//32*4
    //Room::GetInstance()->worldTransofrm_.scale = { 4.0f,1.0f,4.0f };
#ifdef _DEBUG

	if (ImGui::TreeNode("Room"))
	{
		ImGui::ColorPicker4("color", &Room::GetInstance()->color_.x);
		ImGui::DragFloat3("translate", &Room::GetInstance()->worldTransofrm_.translate.x);
		//ImGui::DragFloat3("scale", &Room::GetInstance()->worldTransofrm_.scale.x);
		ImGui::DragFloat("metalness", &Room::GetInstance()->metalness_);
		ImGui::DragFloat("roughness", &Room::GetInstance()->roughness_);
		ImGui::DragFloat("specular", &Room::GetInstance()->Specular_);
		ImGui::DragFloat3("scale", &Room::GetInstance()->worldTransofrm_.scale.x);
		ImGui::TreePop();
	}
#endif // _DEBUG
	SettingMaterial_Param();

	Room::GetInstance()->worldTransofrm_.UpdateMatrix();
}

void Room::Draw(ViewProjection view)
{
	Room::GetInstance()->gameObject_->Draw(Room::GetInstance()->worldTransofrm_, view);
}

void Room::SettingMaterial_Param()
{
	Room::GetInstance()->gameObject_->SetColor(Room::GetInstance()->color_);
	Room::GetInstance()->gameObject_->SetRoughness(Room::GetInstance()->roughness_);
	Room::GetInstance()->gameObject_->SetSpecular(Room::GetInstance()->Specular_);
	Room::GetInstance()->gameObject_->SetMetalness(Room::GetInstance()->metalness_);

}
