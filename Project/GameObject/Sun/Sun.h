#pragma once
#include"Game3dObject.h"
#include"Light/LightingManager.h"
#include"SunManager.h"

class Sun
{
public:
	Sun() {};
	~Sun() {};

	void Initialize(Vector3 pos={}, float intencity=1.0f);

	void Update();

	void Draw(ViewProjection view);

	void SetPos(Vector3 pos);

	Vector3 getPos() { return LeftLight_.position; }

	void SetDecay(float d) { LeftLight_.decay = d; };

	void SetIntencity(float i) { LeftLight_.intencity = i; }

	void SetLightParam(PointLight_param p) { LeftLight_ = p; }
private:

	PointLight_param LeftLight_ = {};
	PointLight_param RightLight_ = {};

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
};