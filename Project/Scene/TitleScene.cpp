#include "TitleScene.h"
#include <EllysiaAudio/Audio.h>

void TitleScene::Initialize()
{
	titleName_ = make_unique<TitleName>();
	titleName_->Initialize();
	backTex_ = make_unique<BackTitleSceneSprite>();
	backTex_->Initlaize();

	inputHandler_ = make_unique<TitleInputHandler>();
	inputHandler_->Initialize();


	SceneChangeAnimation::Initialize();
	Room::Initialize();
	viewProjection_.Initialize();

	sun_ = make_unique<Sun>();
	sun_->Initialize({0.0f,478.0f,0.0f});
	sun_->SetIntencity(1.2f);

	push_space = make_unique<SpacePushSprite>();
	push_space->Initialize();

	viewProjection_.translation_ = {0.0f,-3.0f,0.0f};
	
	//時計
	Clock::Initialize();
	
	//絵
	Illustration::Initialize();
	
	//机
	Desk::Initialize();
	

	ModelManager::ModelLoadNormalMap();
	uint32_t modelHandle = ModelManager::LoadObjectFile("TestMonkey");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle);
	gameObject_->UseLight(true);
	gameObject_->SetlectModelPipeline(UE4_BRDF);


	bgmHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Title/Title.wav");
	startSEHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Deside/StageDeside.wav");



	bgmAudio_ = Audio::GetInstance();
	bgmAudio_->PlayWave(bgmHandle_, true);
	bgmAudio_->ChangeVolume(bgmHandle_, 0.8f);
}

void TitleScene::Update(GameManager* Scene)
{
	//時計
	Clock::Update();
	sun_->Update();
	viewProjection_.rotation_.y += 0.001f;
	//1度だけすべての更新をする
	if (!Initialize1Update())
	{
		Initialize1UpdateLock_ = true;
	}

#ifdef _DEBUG
	if (ImGui::Button("ChangeScene"))
	{
		isChangeScene_ = true;
	}
	if (ImGui::TreeNode("view"))
	{
		ImGui::DragFloat3("translate", &viewProjection_.translation_.x);
		ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, -0.01f, 0.01f);
		ImGui::TreePop();
	}
	
#endif // _DEBUG

	//viewProjection_.rotation_.y += 0.01f;
	SceneChangeAnimation::Update();
	Room::Update();


	//絵
	Illustration::Update();
	
	//机
	Desk::Update();
	

	if (SceneChangeAnimation::GetChangeFinishFlag())
	{
		inputCommand_ = inputHandler_->GetHandleInput();

		if (this->inputCommand_)
		{
			
			inputCommand_->Exec(this);
		}
		backTex_->Update();
		titleName_->Update();
	}

	if (SceneChangeAnimation::GetInstance()->GetSceneChangeFlag() )
	{
		bgmAudio_->StopWave(bgmHandle_);
		Scene->ChangeState(new SelectScene);
		return;
	}

	if (isChangeScene_ )
	{
		Scene->ChangeState(new GameScene);
		return;
	}
	push_space->Update();
	viewProjection_.UpdateMatrix();
	
}

void TitleScene::Back2dSpriteDraw()
{
}

void TitleScene::Object3dDraw()
{
	sun_->Draw(viewProjection_);
	Clock::Draw(viewProjection_);
	
	//絵
	Illustration::Draw(viewProjection_);
	//机
	Desk::Draw(viewProjection_);
	
	Room::Draw(viewProjection_);
}

void TitleScene::Flont2dSpriteDraw()
{

	push_space->Draw(viewProjection_);
	titleName_->Draw(viewProjection_);
	SceneChangeAnimation::Draw(viewProjection_);
}

bool TitleScene::Initialize1Update()
{
	inputCommand_ = inputHandler_->GetHandleInput();

	if (this->inputCommand_)
	{
		inputCommand_->Exec(this);
	}

	titleName_->Update();
	backTex_->Update();
	viewProjection_.UpdateMatrix();

	return Initialize1UpdateLock_;
}
