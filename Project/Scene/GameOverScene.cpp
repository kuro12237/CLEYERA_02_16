#include "GameOverScene.h"

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{

	space_Push_ = make_unique<SpacePushSprite>();
	space_Push_->Initialize();

	sun_ = make_unique<Sun>();
	sun_->Initialize();
	sun_->Initialize({ 0.0f,478.0f,0.0f });
	sun_->SetIntencity(2.2f);

	gameOverText_ = make_unique<GameOverSprite>();
	gameOverText_->Initialize();

	viewProjection_.Initialize();

	bgm_ =Audio::GetInstance();
	bgmHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/GameOver/Lose.wav");
	se_ = Audio::GetInstance();
	returnSEHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Deside/Return.wav");

	bgm_->PlayWave(bgmHandle_, true);
}

void GameOverScene::Update(GameManager* Scene)
{
	Scene;
	SceneChangeAnimation::Update();

	if (SceneChangeAnimation::GetChangeFinishFlag())
	{

		if (Input::PushKeyPressed(DIK_SPACE) || Input::PushBottonPressed(XINPUT_GAMEPAD_A))
		{
			SceneChangeAnimation::SetChangeFinishFlag(false);
		}

	}
	if (SceneChangeAnimation::GetInstance()->GetSceneChangeFlag())
	{
		bgm_->StopWave(bgmHandle_);
		Scene->ChangeState(new TitleScene);
		return;
	}
	sun_->Update();
	Room::Update();
	gameOverText_->Update();
	space_Push_->Update();
	viewProjection_.UpdateMatrix();
}

void GameOverScene::Back2dSpriteDraw()
{
}

void GameOverScene::Object3dDraw()
{
	Room::Draw(viewProjection_);
}

void GameOverScene::Flont2dSpriteDraw()
{
	space_Push_->Draw(viewProjection_);
	gameOverText_->Draw(viewProjection_);
	SceneChangeAnimation::Draw(viewProjection_);
}
