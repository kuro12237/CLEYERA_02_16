#include "TitleInputHandler.h"


ITitleCommand* TitleInputHandler::GetHandleInput()
{
	if (Input::PushKeyPressed(DIK_SPACE))
	{
		return pushCbLSpace_.get();
	}

	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		return pushCbLSpace_.get();
	}

	return nullptr;
}

void TitleInputHandler::Initialize()
{
	this->pushCbLSpace_ = make_unique<TitleSceneChangeCommand>();

}
