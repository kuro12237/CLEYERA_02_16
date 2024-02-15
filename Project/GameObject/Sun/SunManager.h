#pragma once
#include"Light/Light.h"

class SunManager
{
public:
	SunManager() {};
	~SunManager() {};

	static SunManager* GetInstance();

	static void SetNormalPalamerter();

	static void SetHardPalamerter();

	static PointLight_param GetParam() { return SunManager::GetInstance()->param_; }

	static bool GetPlayerFlag() { return SunManager::GetInstance()->SetPlayer; }

private:
	PointLight_param param_{};

	bool SetPlayer = false;

};