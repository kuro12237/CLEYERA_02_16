#include "GameClearScene.h"

void GameClearScene::Initialize()
{
	space_Push_ = make_unique<SpacePushSprite>();
	space_Push_->Initialize();

	clearText_ = make_unique<GameClearText>();
	clearText_->Initialize();

	sun_ = make_unique<Sun>();
	sun_->Initialize();
	sun_->Initialize({ 0.0f,478.0f,0.0f });
	sun_->SetIntencity(2.2f);

	viewProjection_.Initialize();

	bgm_ = Audio::GetInstance();
	bgmHandle_ = Audio::GetInstance()->LoadWave("Resources/Sounds/Result/Win.wav");
	bgm_->PlayWave(bgmHandle_, true);
}

void GameClearScene::Update(GameManager* Scene)
{
	SceneChangeAnimation::Update();
	if (SceneChangeAnimation::GetChangeFinishFlag())
	{
		if (Input::PushKeyPressed(DIK_SPACE) || Input::PushBottonPressed(XINPUT_GAMEPAD_A))
		{
			bgm_->StopWave(bgmHandle_);
			SceneChangeAnimation::SetChangeFinishFlag(false);
			TitleSceneFlag_ = true;
		}

	}
	if (SceneChangeAnimation::GetInstance()->GetSceneChangeFlag()&&TitleSceneFlag_)
	{
		Scene->ChangeState(new TitleScene);
		return;
	}

	sun_->Update();
	
	Room::Update();

	clearText_->Update();
	space_Push_->Update();
	viewProjection_.UpdateMatrix();
}

void GameClearScene::Back2dSpriteDraw()
{
}

void GameClearScene::Object3dDraw()
{
	Room::Draw(viewProjection_);
}

void GameClearScene::Flont2dSpriteDraw()
{
	clearText_->Draw(viewProjection_);
	space_Push_->Draw(viewProjection_);
	SceneChangeAnimation::Draw(viewProjection_);
}
