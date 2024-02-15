#pragma once
#include"Sprite/Sprite.h"
#include <EllysiaAudio/Audio.h>

class GameStartCount
{
public:
	GameStartCount() {};
	~GameStartCount() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

#pragma region get

	bool GetCountFinishFlag() { return isCountFinishFlag_; }

#pragma endregion

private:

	int32_t DeltaTimer();

	void ColorUpdate(int32_t prevTime);

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t texHandle_ = 0;

	const int32_t kFlameMaxTimer_ = 60;
	int32_t flameTime_ = 1;

	int32_t timeCount_ = 4;
	int32_t newCountTime_ = 60 * 3;

	bool isCountFinishFlag_ = false;

	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	struct  src
	{
		Vector2 Lt;
		Vector2 Lb;
		Vector2 Rt;
		Vector2 Rb;
	};

	src CountNumber_[6] = {};

	Audio* countSE_ = nullptr;
	uint32_t countSEHandle_ = 0u;

	Audio* startSE_ = nullptr;
	uint32_t startSEHandle_ = 0u;
};
