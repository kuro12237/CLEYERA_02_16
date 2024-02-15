#pragma once

class SceneChangeAnimation;
class ISceneChangeAnimationState
{
public:

	virtual~ISceneChangeAnimationState() {};

	virtual void Update(SceneChangeAnimation *state) = 0;


private:

};
