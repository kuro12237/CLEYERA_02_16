#pragma once
#include"Game3dObject.h"
#include "Sprite/Sprite.h"
#include "CollisionManager.h"
#include "OBBCollider.h"

enum GroundState {
	Bad,
	More,
	Good
};


class Ground : public OBBCollider
{
public:
	Ground() {};
	~Ground() {};

	void Initialize(Vector3 pos = {}, Vector3 size = {}, Vector3 spritePos = {}, uint32_t heel = 8, uint32_t damege = 3);

	void Update();

	void DrawF2D(ViewProjection view);
	void Draw3D(ViewProjection view);

	void OnCollision(uint32_t id) override;

	Vector3& GetGroundSize() { return Scale_; }

	int GetHP() { return this->HP_; }
	void SetHP(int hp) { HP_ = hp; }

	uint32_t GetLevel() { return this->Level_; }

	GroundState GetGroundState() { return this->state_; }


#pragma region Colliderで使うゲッター

	Vector3 GetWorldPosition() override;

	Vector3 GetSize() override { return this->size_; }

	Vector3 GetRotate() override { return this->worldTrabsform.rotation; }

#pragma endregion 

	float GetGroundHeight() const {
		return GROUND_TRANSLATE_;
	}


private: // メンバ関数

	/// <summary>
	/// OBBColliderのセッティング
	/// </summary>
	void SettingOBB();

	/// <summary>
	/// Colliderのビットのセッティング
	/// </summary>
	void SettingColliderBit();

	/// <summary>
	/// HPによってレベルが変わる
	/// </summary>
	void CalcLevel();

	/// <summary>
	/// HP用スプライトの更新処理
	/// </summary>
	void SpriteHPUpdate();

	/// <summary>
	/// 色の変更
	/// </summary>
	Vector4 ConvertColor(Vector4 old_Color, Vector3 new_Color);

	/// <summary>
	/// ラベルの設定
	/// </summary>
	void LavelUpdate();

private:
	const float GROUND_TRANSLATE_ = 1.5f;


	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTrabsform = {};

	Vector3 Scale_ = { 1.0f, 1.0f, 1.0f };
	Vector3 translate_ = { 0.0f,0.0f,0.0f };
	Vector4 color_{};

	Vector3 size_{};

	uint32_t Level_;
	int HP_;

	bool isHit_;

	uint32_t damage_ = 0;
	uint32_t heel_ = 0;

	unique_ptr<Sprite> spriteHP_ = nullptr;
	WorldTransform spriteWT_{};
	uint32_t HPTexHD_;
	Vector4 spColor_{};

	unique_ptr<Sprite> labelSp_ = nullptr;
	WorldTransform labelWt_{};

	uint32_t labelG_;
	uint32_t labelM_;
	uint32_t labelB_;

	GroundState state_{};
};

