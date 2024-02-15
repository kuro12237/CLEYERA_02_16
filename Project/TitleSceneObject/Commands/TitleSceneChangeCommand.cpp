#include "TitleSceneChangeCommand.h"

void TitleSceneChangeCommand::Exec(IScene* scene)
{
	scene;
	
	if (SceneChangeAnimation::GetChangeFinishFlag())
	{
		SceneChangeAnimation::SetChangeFinishFlag(false);
	}

}
