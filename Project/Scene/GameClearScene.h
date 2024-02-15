#pragma once
#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"

#include"GameObject/Player/Player.h"
#include"GameObject/Ground/Ground.h"
#include"GameObject/Sun/Sun.h"
#include "GameObject/EnemyManager/EnemyManager.h"
#include"GameObject/GameStartCount/GameStartCount.h"

#include"SceneChangeAnimation/SceneChangeAnimation.h"
#include"Room/Room.h"
#include"GameOverScene.h"
#include"PushObject/SpacePushSprite.h"
#include"GameClearObject/GameClearText.h"
#include "EllysiaAudio/Audio.h"

class GameClearScene :public IScene
{
public:
	GameClearScene() {};
	~GameClearScene() {
		bgm_->StopWave(bgmHandle_);
	};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	unique_ptr<SpacePushSprite>space_Push_ = nullptr;
	unique_ptr<GameClearText>clearText_ = nullptr;
	ViewProjection viewProjection_ = {};
	unique_ptr<Sun>sun_ = nullptr;

	Audio* bgm_ = nullptr;
	uint32_t bgmHandle_ = 0u;

	bool TitleSceneFlag_ = false;
};