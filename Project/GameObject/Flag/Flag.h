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
	/// ����������
	/// </summary>
	void Initialize(uint32_t modelHD, Vector3 position);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(Vector3 position);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(ViewProjection view);
	
	/// <summary>
	/// �Փˎ��R�[���o�b�O�֐�
	/// </summary>
	void OnCollision(uint32_t id) override;


#pragma region Get

	/// <summary>
	/// ���[���h���W�̎擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition() override;

	/// <summary>
	/// �T�C�Y�̎擾
	/// </summary>
	Vector3 GetSize() override { return this->size_; }

#pragma endregion


#pragma region Set

	/// <summary>
	/// Collider�̃r�b�g�̐ݒ�
	/// </summary>
	void SettingColliderBit();

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	void SetPosition(Vector3 position) { worldTransform_.translate = position; }

	/// <summary>
	/// OBB�̐ݒ�
	/// </summary>
	void SettingOBB();

#pragma endregion


private:

	unique_ptr<Game3dObject> object_ = nullptr;
	WorldTransform worldTransform_{};

	Vector3 size_{};
};

