#pragma once
#include"Sprite/Sprite.h"
#include"state/SceneChangeAnimationDownState.h"
#include"state/SceneChangeAnimationUpState.h"

class SceneChangeAnimation
{
public:
	
	static SceneChangeAnimation* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

#pragma region Get

	static const WorldTransform& GetWorldTransform() { return SceneChangeAnimation::GetInstance()->worldTransform_; }

	static bool GetSceneChangeFlag() { return SceneChangeAnimation::GetInstance()->SceneChangeFlag_; }
	
	static bool GetChangeFinishFlag() { return SceneChangeAnimation::GetInstance()->changeFinishFlag_; }

#pragma endregion

#pragma region Set

	static void SetTranslate(Vector3 t) { SceneChangeAnimation::GetInstance()->worldTransform_.translate = t; }

	static void SetSceneChangeFlag(bool Flag) { SceneChangeAnimation::GetInstance()->SceneChangeFlag_ = Flag; }

	static void SetChangeFinishFlag(bool flag) { SceneChangeAnimation::GetInstance()->changeFinishFlag_ = flag; }

	static void SetChangeEndFlag(bool flag) { SceneChangeAnimation::GetInstance()->changeEndFlag_ = flag;}

	static void SetChangeStartFlag(bool flag) { SceneChangeAnimation::GetInstance()->changeStartFlag_ = flag; }

#pragma endregion

private:

	bool InitializeLock_ = false;

	uint32_t sceneChangeTexHandle_ = 0;
	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};

	unique_ptr<ISceneChangeAnimationState>state_ = nullptr;

	bool SceneChangeFlag_ = false;
	
	bool changeStartFlag_ = false;
	bool changeEndFlag_ = false;
	bool changeFinishFlag_ = true;

};
