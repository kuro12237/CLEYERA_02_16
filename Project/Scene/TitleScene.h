#pragma once
#include"Game3dObject.h"
#include"IScene.h"

#include"TitleSceneObject/TitleName.h"
#include"TitleSceneObject/InputHandler/TitleInputHandler.h"
#include"GameScene.h"
#include"SceneChangeAnimation/SceneChangeAnimation.h"
#include"TitleSceneObject/BackTitle/BackTitleSceneSprite.h"
#include"Room/Room.h"
#include"GameObject/Sun/Sun.h"
#include"PushObject/SpacePushSprite.h"
#include"SelectScene.h"
#include"../GameObject/Clock/Clock.h"
#include"../Illustration/Illustration.h"
#include"../GameObject/Desk/Desk.h"
#include"GameObject/AttackParticle/AttackParticle.h"

#include "EllysiaAudio/Audio.h"
class TitleScene:public IScene
{
public:
	TitleScene() {};
	~TitleScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	
	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	bool Initialize1Update();

	ViewProjection viewProjection_ = {};

	unique_ptr<TitleName>titleName_ = nullptr;
	unique_ptr<BackTitleSceneSprite>backTex_ = nullptr;
	unique_ptr<TitleInputHandler>inputHandler_ = nullptr;

	ITitleCommand*inputCommand_ = nullptr;

	bool isChangeScene_ = false;
	bool Initialize1UpdateLock_ = false;
	unique_ptr<Sun>sun_ = nullptr;

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};

	unique_ptr<SpacePushSprite>push_space = nullptr;

	float metalness_=0.0f;
	float specular_ = 0.0f;
	float rougness_ = 0.0f;


	Audio* bgmAudio_=nullptr;
	uint32_t bgmHandle_ = 0u;
	uint32_t startSEHandle_ = 0u;
	float scatterCoefficient=0.5f;
	float absorptionCoefficient = 0.5f;
	float scatterDistance = 0.5f;


};

