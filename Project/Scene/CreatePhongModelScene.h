#pragma once
#include"Model.h"
#include"IScene.h"

class CreatePhongModelScene :public IScene
{
public:
	CreatePhongModelScene() {};
	~CreatePhongModelScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:
};