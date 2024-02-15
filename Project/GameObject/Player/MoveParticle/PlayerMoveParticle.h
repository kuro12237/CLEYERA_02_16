#pragma once
#include"Particle/Particle.h"

class PlayerMoveParticle
{
public:
	PlayerMoveParticle() {};
	~PlayerMoveParticle() {};

	static PlayerMoveParticle* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

	static void Spown(Vector3 pos);
private:

	unique_ptr<Particle>particle_ = nullptr;
	list<Particle_param> param_ = {};

	int32_t spownTimer_ = 0;
	const int32_t kSpownTimer_ = 2;
	random_device device_ = {};
	bool InitializeLock_ = false;
};

