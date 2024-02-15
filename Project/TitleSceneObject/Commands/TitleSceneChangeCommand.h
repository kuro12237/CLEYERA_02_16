#pragma once
#include"TitleSceneObject/TitleCommand.h"
#include"LogManager.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"SceneChangeAnimation/SceneChangeAnimation.h"

class TitleSceneChangeCommand:public ITitleCommand
{
public:
	
	void Exec(IScene* scene)override;

private:

};