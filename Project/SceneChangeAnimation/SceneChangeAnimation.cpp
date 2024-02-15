#include "SceneChangeAnimation.h"

SceneChangeAnimation* SceneChangeAnimation::GetInstance()
{
	static SceneChangeAnimation instance;
	return &instance;
}

void SceneChangeAnimation::Initialize()
{
	if (!SceneChangeAnimation::GetInstance()->InitializeLock_)
	{
		SceneChangeAnimation::GetInstance()->sceneChangeTexHandle_ = TextureManager::LoadPngTexture("changeScene/changeSceneTex.png");

		Vector2 texSize = TextureManager::GetTextureSize(SceneChangeAnimation::GetInstance()->sceneChangeTexHandle_);

		texSize.x *= -0.5f;
		texSize.y *= -0.5f;

		SceneChangeAnimation::GetInstance()->sprite_ = make_unique<Sprite>();
		SceneChangeAnimation::GetInstance()->sprite_->Initialize(new SpriteBoxState,texSize);
		SceneChangeAnimation::GetInstance()->sprite_->SetTexHandle(SceneChangeAnimation::GetInstance()->sceneChangeTexHandle_);

		SceneChangeAnimation::GetInstance()->worldTransform_.Initialize();
		SceneChangeAnimation::GetInstance()->worldTransform_.translate = { 640.0f,-360.0f };

		SceneChangeAnimation::GetInstance()->InitializeLock_ = true;
	}

}

void SceneChangeAnimation::Update()
{
#ifdef _DEBUG

	if (ImGui::TreeNode("SceneChangeAnimation")){
		ImGui::DragFloat3("pos:xyz", &SceneChangeAnimation::GetInstance()->worldTransform_.translate.x);
		ImGui::TreePop();
	}

#endif // _DEBUG

	///stateをnull
	if (SceneChangeAnimation::GetInstance()->changeFinishFlag_)
	{
		SceneChangeAnimation::GetInstance()->state_.release();
		SceneChangeAnimation::GetInstance()->SceneChangeFlag_ = false;
		SceneChangeAnimation::GetInstance()->changeStartFlag_ = false;
		SceneChangeAnimation::GetInstance()->changeEndFlag_ = false;
	}

	//開始
	if (!SceneChangeAnimation::GetInstance()->changeFinishFlag_ 
		&& 
		!SceneChangeAnimation::GetInstance()->changeStartFlag_
		&&
		!SceneChangeAnimation::GetInstance()->changeEndFlag_
		)
	{
		SceneChangeAnimation::GetInstance()->changeStartFlag_ = true;
		SceneChangeAnimation::GetInstance()->state_ = make_unique<SceneChangeAnimationDownState>();
	}

	//切替後の処理
	if (!SceneChangeAnimation::GetInstance()->changeFinishFlag_
		&&
		!SceneChangeAnimation::GetInstance()->changeStartFlag_
		&&
		SceneChangeAnimation::GetInstance()->changeEndFlag_
		&&
		SceneChangeAnimation::GetInstance()->SceneChangeFlag_
		)
	{
		SceneChangeAnimation::GetInstance()->state_ = make_unique<SceneChangeAnimationUpState>();
	}

	//changeするタイミングのフラグの後処理
	if (SceneChangeAnimation::GetInstance()->SceneChangeFlag_)
	{
		SceneChangeAnimation::GetInstance()->SceneChangeFlag_ = false;
	}

	if (SceneChangeAnimation::GetInstance()->state_)
	{
		SceneChangeAnimation::GetInstance()->state_->Update(SceneChangeAnimation::GetInstance());
	}

	SceneChangeAnimation::GetInstance()->worldTransform_.UpdateMatrix();
}

void SceneChangeAnimation::Draw(ViewProjection view)
{
	SceneChangeAnimation::GetInstance()->sprite_->Draw(SceneChangeAnimation::GetInstance()->worldTransform_, view);
}
