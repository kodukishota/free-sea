#include "Actor3D.h"
#include "ActorCollision3D.h"
#include "Collider3D.h"

// �R���X�g���N�^
Actor3D::Actor3D(const char* name, const Vector3& position, int itemNum) :
	m_name(name),
	m_itemNum(itemNum),
	m_collider(nullptr)
{
	m_transform.position = position;
}

// ���\�[�X�̓ǂݍ���
void Actor3D::Load()
{
	// �Փ˔���V�X�e���ɓo�^
	if (m_collider)
	{
		ActorCollision3D::GetInstance()->Register(this);
	}
}

// ���\�[�X�̉��
void Actor3D::Release()
{
	// �Փ˔���V�X�e�����珜�O
	if (m_collider)
	{
		ActorCollision3D::GetInstance()->Remove(this);
		delete m_collider;
		m_collider = nullptr;
	}
}

// �`��
void Actor3D::Draw()
{
	Node::Draw();
}

// �q�m�[�h���܂ލX�V
void Actor3D::TreeUpdate()
{
	// Node�{����TreeUpdate�����s
	Node::TreeUpdate();
}
