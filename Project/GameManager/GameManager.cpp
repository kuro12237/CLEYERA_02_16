#include "GameManager.h"

GameManager::GameManager()
{
	Cleyera::Initialize();

	Scene_ = new GameScene();

	Scene_->Initialize();
}

GameManager::~GameManager()
{
	delete Scene_;
	Cleyera::Finalize();
}

void GameManager::Run()
{
	while (WinApp::WinMsg())
	{
		Cleyera::BeginFlame();

#ifdef  _USE_IMGUI
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));
		ImGui::Begin("DebugTreeNode");
		WinApp::ImGuiUpdate();
		DirectXCommon::ImGuiUpdate();

#endif //  _USE_IMGUI

		LightingManager::ClearList();
		Scene_->Update(this);
		LightingManager::TransfarBuffers();

#ifdef  _USE_IMGUI
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
#endif // _USE_IMGUI

		DirectXCommon::PreDraw();

		Scene_->Back2dSpriteDraw();
		Scene_->Object3dDraw();
		Scene_->Flont2dSpriteDraw();

		Cleyera::EndFlame();
		DirectXCommon::PostDraw();
	}
}

void GameManager::ChangeState(IScene *newScene)
{
	DebugTools::ClearCommand();

	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	Scene_->Update(this);
	return;
}
