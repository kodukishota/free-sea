#include "Actor.h"
#include "ActorCollision.h"
#include "Collider.h"

// �R���X�g���N�^
Actor::Actor(const char* name, const char* textureName, const Vector2& position) :
	m_name(name),
	m_sprite(nullptr),
	m_collider(nullptr)
{
	m_transform.position = position;

	// �摜���ݒ肳��Ă����Sprite���N��
	if (textureName)
	{
		m_sprite = new Sprite();
		m_sprite->Register(textureName);
	}
}

// ���\�[�X�̓ǂݍ���
void Actor::Load()
{
	if (m_sprite)
	{
		m_sprite->Load();
	}

	// �Փ˔���V�X�e���ɓo�^
	if (m_collider)
	{
		ActorCollision::GetInstance()->Register(this);
	}
}

// ���\�[�X�̉��
void Actor::Release()
{
	if (m_sprite)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}

	// �Փ˔���V�X�e�����珜�O
	if (m_collider)
	{
		ActorCollision::GetInstance()->Remove(this);
		delete m_collider;
		m_collider = nullptr;
	}
}

// �`��
void Actor::Draw()
{
	if (m_sprite)
	{
		m_sprite->Draw(m_transform);
	}
}

// �q�m�[�h���܂ލX�V
void Actor::TreeUpdate()
{
	// Node�{����TreeUpdate�����s
	Node::TreeUpdate();

	// �X�v���C�g�̍X�V
	if (m_sprite)
	{
		m_sprite->Update();
	}
}
