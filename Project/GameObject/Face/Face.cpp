#include "Face.h"

Face* Face::GetInstance()
{
	static Face instance;
	return &instance;
}

void Face::Initialize()
{
	if (!Face::GetInstance()->InitializeLock_)
	{


		ModelManager::ModelUseSubsurface();
		Face::GetInstance()->modelHandle_ = ModelManager::LoadObjectFile("Face");
		Face::GetInstance()->Fes = make_unique<Game3dObject>();
		Face::GetInstance()->Fes->Create();
		Face::GetInstance()->Fes->SetModel(Face::GetInstance()->modelHandle_);
		Face::GetInstance()->Fes->UseLight(true);
		Face::GetInstance()->Fes->SetlectModelPipeline(PHONG_SUBSURFACE_MODEL);
		Face::GetInstance()->fespos.Initialize();
		Face::GetInstance()->fespos.scale = { 16.0f,14.0f,14.0f };
		Face::GetInstance()->fespos.rotation = { 0.0f,0.0f,0.0f };
		Face::GetInstance()->fespos.translate = { -3.0f,-12.0f,95.0f };
		Face::GetInstance()->InitializeLock_ = true;
	}
}
void Face::Draw(ViewProjection view)
{
	Face::GetInstance()->fespos.UpdateMatrix();
	Face::GetInstance()->Fes->SetColor(Face::GetInstance()->color2_);
	Face::GetInstance()->Fes->SetRoughness(Face::GetInstance()->roughness2_);
	Face::GetInstance()->Fes->SetSpecular(Face::GetInstance()->Specular_);
	Face::GetInstance()->Fes->SetMetalness(Face::GetInstance()->metalness2_);
#ifdef _DEBUG

	if (ImGui::TreeNode("Face"))
	{
		ImGui::SliderFloat3("Rotate", &Face::GetInstance()->fespos.rotation.x, -3.0f, 3.0f);
		ImGui::DragFloat3("Translate", &Face::GetInstance()->fespos.translate.x, -5.0f, 5.0f);
		ImGui::DragFloat3("scale", &Face::GetInstance()->fespos.scale.x, -5.0f, 5.0f);
		ImGui::TreePop();
	}

#endif // _DEBUG
	Face::GetInstance()->Fes->Draw(Face::GetInstance()->fespos, view);
}
