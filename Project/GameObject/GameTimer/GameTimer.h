#pragma once
#include"Sprite/Sprite.h"
#include"VectorTransform.h"
#include"Model.h"
#include <EllysiaAudio/Audio.h>

class GameTimer
{
public:
	GameTimer() {};
	~GameTimer() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	bool GetIsFinish() { return isFinish_; }
private:

	uint32_t DeltaTimer();

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	unique_ptr<Sprite>SpriteLog_ = nullptr;
	WorldTransform  spriteLogWorldTransform_ = {};

	float Flame_ = 0.0f;
	const float kFlame_ = 60.0f;

	int32_t Timer_ = 60;
	int32_t kTimer_ = 0;

	Vector4 SpriteColor_ = { 0.0f,1.0f,0.0f,1.0f };

	bool isFinish_ = false;

	
};
