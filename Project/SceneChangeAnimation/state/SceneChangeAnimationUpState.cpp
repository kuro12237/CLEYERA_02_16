#include "SceneChangeAnimationUpState.h"

void SceneChangeAnimationUpState::Update(SceneChangeAnimation* state)
{
	nowFlame_ += 0.8f;

	Move(state);

	if (state->GetWorldTransform().translate.y <= endPos_.y)
	{
		state->SetChangeFinishFlag(true);
		state->SetChangeEndFlag(false);
	}
}

void SceneChangeAnimationUpState::Move(SceneChangeAnimation* state)
{
	if (nowFlame_ <= endFlame_)
	{
		Vector3 startpos = state->GetWorldTransform().translate;
		Vector3 pos = startpos;
		pos.y = pos.y + (endPos_.y - startpos.y) * VectorTransform::easeOutBounce(float(nowFlame_) / endFlame_);
		state->SetTranslate(pos);
	}
}
