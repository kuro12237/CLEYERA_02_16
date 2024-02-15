#pragma once
#include "Vector3.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "OBBCollider.h"
#include "SphereCollider.h"
#include "GameObject/RandomGenerator/RandomGenerator.h"
#include <array>

// エネミーのタイプ名enumで定義
enum EnemyType {
	Normal,
	Power,
	Stan,
};

/* IEnemyType */
class IEnemyType {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IEnemyType() {};

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	~IEnemyType() {};


	///// 純粋仮想関数　※派生クラスに実装を強制する

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize(int modelID, int MringMode, Vector3 pos, std::array<ScopeVec3, 3> mapScope) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(bool isHit) = 0;

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Draw(ViewProjection view) = 0;

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	virtual bool IsDead() = 0;

	/// <summary>
	/// スポーン処理の終了フラグ
	/// </summary>
	virtual bool IsSpanwFinished() = 0;

	/// <summary>
	/// Colliderの取得
	/// </summary>
	virtual OBBCollider* GetOBBCollider() = 0;

protected:

};