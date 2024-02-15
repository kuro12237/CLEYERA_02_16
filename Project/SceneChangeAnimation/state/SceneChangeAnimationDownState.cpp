#include "SceneChangeAnimationDownState.h"

void SceneChangeAnimationDownState::Update(SceneChangeAnimation* state)
{
	nowFlame_ += 0.8f;

	Move(state);

	if (state->GetWorldTransform().translate.y >= endPos_.y)
	{
		state->SetSceneChangeFlag(true);
		state->SetChangeEndFlag(true);
		state->SetChangeStartFlag(false);
	}
}

void SceneChangeAnimationDownState::Move(SceneChangeAnimation* state)
{
	if (nowFlame_ <= endFlame_)
	{
		Vector3 startpos = state->GetWorldTransform().translate;
		Vector3 pos = startpos;
		pos.y = pos.y + (endPos_.y - startpos.y) * VectorTransform::easeOutBounce(float(nowFlame_) / endFlame_);
		state->SetTranslate(pos);
	}
}

Vector3 SceneChangeAnimationDownState::BounseLeap(Vector3 s, Vector3 e, float t)
{
	return Vector3(
		s.x + (e.x - s.x) * VectorTransform::easeOutBounce(t),
		s.y + (e.y - s.y) * VectorTransform::easeOutBounce(t),
		s.z + (e.z - s.z) * VectorTransform::easeOutBounce(t)
	);

}
