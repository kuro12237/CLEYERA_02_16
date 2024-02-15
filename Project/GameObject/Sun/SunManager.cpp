#include "SunManager.h"

SunManager* SunManager::GetInstance()
{
	static SunManager instance;
    return &instance;
}

void SunManager::SetNormalPalamerter()
{
	SunManager::GetInstance()->param_.decay = 0.5f;
	SunManager::GetInstance()->param_.position = { 76.0f,32.0f,-100.0f };
	SunManager::GetInstance()->param_.radious = 1280.0f;
	SunManager::GetInstance()->param_.intencity = 1.2f;
	SunManager::GetInstance()->param_.decay = 1.5f;
	SunManager::GetInstance()->SetPlayer = false;
}

void SunManager::SetHardPalamerter()
{
	SunManager::GetInstance()->param_.decay = 0.5f;
	SunManager::GetInstance()->param_.position = { 0.0f,0.0f,0.0f };
	SunManager::GetInstance()->param_.radious = 16.0f;
	SunManager::GetInstance()->param_.intencity = 1.2f;
	SunManager::GetInstance()->param_.decay = 1.5f;
	SunManager::GetInstance()->SetPlayer = true;
}
