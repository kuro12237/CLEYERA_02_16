#include "PlayerMoveParticle.h"

PlayerMoveParticle* PlayerMoveParticle::GetInstance()
{
	static PlayerMoveParticle instance;
	return &instance;
}

void PlayerMoveParticle::Initialize()
{
	if (!PlayerMoveParticle::GetInstance()->InitializeLock_)
	{
		PlayerMoveParticle::GetInstance()->particle_ = make_unique<Particle>();
		PlayerMoveParticle::GetInstance()->particle_->Initialize(new ParticlePlaneState, 320);
		uint32_t tex = TextureManager::LoadPngTexture("Player/moveSmoke.png");
		PlayerMoveParticle::GetInstance()->particle_->SetTexHandle(tex);
		PlayerMoveParticle::GetInstance()->InitializeLock_ = true;
	}
}

void PlayerMoveParticle::Update()
{

	PlayerMoveParticle::GetInstance()->param_ = PlayerMoveParticle::GetInstance()->particle_->begin();

	for (Particle_param& p : PlayerMoveParticle::GetInstance()->param_)
	{
		p.color_.w -= 0.04f;
		if (p.color_.w<=0.0f)
		{
			continue;
		}
		PlayerMoveParticle::GetInstance()->particle_->PushList(p);
	}
}

void PlayerMoveParticle::Draw(ViewProjection view)
{
	PlayerMoveParticle::GetInstance()->particle_->Draw(view);

}

void PlayerMoveParticle::Spown(Vector3 pos)
{
	PlayerMoveParticle::GetInstance()->spownTimer_++;
	if (PlayerMoveParticle::GetInstance()->spownTimer_>= PlayerMoveParticle::GetInstance()->kSpownTimer_)
	{
		for (int i = 0; i < 4; i++)
		{
			mt19937 randomEngine(PlayerMoveParticle::GetInstance()->device_());
			uniform_real_distribution<float>distribution(-1.0f, 1.0f);

			Particle_param p;
			p.worldTransform_.translate = VectorTransform::Add(pos, { distribution(randomEngine),0.0f ,distribution(randomEngine) });
			p.color_ = { 1,1,1,1 };
			PlayerMoveParticle::GetInstance()->particle_->PushList(p);
			PlayerMoveParticle::GetInstance()->spownTimer_ = 0;
		}
	}
}
