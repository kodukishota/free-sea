#pragma once
#pragma once
#include "Node.h"
#include "Transform3D.h"
#include <string>

class Collider3D;

class Actor3D : public Node
{
protected:
	std::string m_name;		// �I�u�W�F�N�g��
	Transform3D m_transform;	// �p�����
	Collider3D* m_collider;	// �Փ˔���̌`��

	int m_itemNum;

	virtual void Load() override;		// ���\�[�X�̓ǂݍ���
	virtual void Release() override;	// ���\�[�X�̉��
	virtual void Draw() override;		// �`��

public:
	// �R���X�g���N�^
	Actor3D(
		const char* name,
		const Vector3& position = Vector3(),
		int itemNum = 0
	);

	// �q�m�[�h���܂ލX�V
	virtual void TreeUpdate() override;

	// �p���̎擾
	const Transform3D& GetTransform() const
	{
		return m_transform;
	}

	// ���W�̎擾
	const Vector3& GetPosition() const
	{
		return m_transform.position;
	}

	// ���O�̎擾
	const std::string& GetName() const
	{
		return m_name;
	}

	// �Փ˔���̌`����擾
	const Collider3D* GetCollider() const
	{
		return m_collider;
	}

	int GetItemNum() const
	{
		return m_itemNum;
	}

	// �Փ˃C�x���g
	virtual void OnCollision(const Actor3D* other) {}
};
