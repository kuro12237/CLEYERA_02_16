#pragma once

#include "Input.h"
#include "Game3dObject.h"
#include "ModelManager.h"
#include "CollisionManager.h"


class Flag : public OBBCollider {

public:

	Flag() {};
	~Flag() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(uint32_t modelHD, Vector3 position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(Vector3 position);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);
	
	/// <summary>
	/// 衝突時コールバッグ関数
	/// </summary>
	void OnCollision(uint32_t id) override;


#pragma region Get

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition() override;

	/// <summary>
	/// サイズの取得
	/// </summary>
	Vector3 GetSize() override { return this->size_; }

#pragma endregion


#pragma region Set

	/// <summary>
	/// Colliderのビットの設定
	/// </summary>
	void SettingColliderBit();

	/// <summary>
	/// 座標の設定
	/// </summary>
	void SetPosition(Vector3 position) { worldTransform_.translate = position; }

	/// <summary>
	/// OBBの設定
	/// </summary>
	void SettingOBB();

#pragma endregion


private:

	unique_ptr<Game3dObject> object_ = nullptr;
	WorldTransform worldTransform_{};

	Vector3 size_{};
};

