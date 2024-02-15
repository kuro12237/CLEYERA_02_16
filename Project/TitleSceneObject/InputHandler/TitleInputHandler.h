#pragma once
#include"Input.h"
#include"TitleSceneObject/Commands/TitleSceneChangeCommand.h"
#include "EllysiaAudio/Audio.h"

class TitleInputHandler
{
public:
	
	ITitleCommand* GetHandleInput();

	void Initialize();

private:

	unique_ptr<ITitleCommand> pushCbLSpace_ = nullptr;
};