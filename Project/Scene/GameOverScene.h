#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"

#include"GameObject/Sun/Sun.h"
#include"SceneChangeAnimation/SceneChangeAnimation.h"
#include"Room/Room.h"
#include"TitleScene.h"
#include"PushObject/SpacePushSprite.h"
#include"GameOverObject/GameOverSprite.h"
#include "EllysiaAudio/Audio.h"

class GameOverScene :public IScene
{
public:
	GameOverScene() {};
	~GameOverScene();

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	unique_ptr<SpacePushSprite>space_Push_ = nullptr;
	ViewProjection viewProjection_ = {};
	unique_ptr<Sun>sun_ = nullptr;

	unique_ptr<GameOverSprite>gameOverText_ = nullptr;

	Audio* bgm_ = nullptr;
	uint32_t bgmHandle_ = 0u;

	Audio* se_ = nullptr;
	uint32_t returnSEHandle_ = 0u;

};