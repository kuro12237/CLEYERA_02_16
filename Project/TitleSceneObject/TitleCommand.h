#pragma once

class TitleInputHandler;
class IScene;

class ITitleCommand
{
public:
	
	virtual void Exec(IScene* scene) = 0;
private:

};
