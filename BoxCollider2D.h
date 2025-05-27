#pragma once
#include "Collider.h"
#include "Collision.h"
#include "DxLib.h"

class BoxCollider2D : public Collider
{
public:
	Vector2 size;	// ���E����

	// �R���X�g���N�^
	BoxCollider2D(const Vector2& size, const Vector2& offset = Vector2(0, 0)) :
		Collider(offset),
		size(size) {}

	// �Փ˔���
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collider2) const override
	{
		// �_�u���f�B�X�p�b�`�ɂ��`�󎯕ʂ�����
		return collider2->CheckCollision(transform2, transform1, this);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider2D* collider2) const override
	{
		// ��`�~��`
		return Collision::Check(transform1, this, transform2, collider2);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider2D* collider2) const override
	{
		// ��`�~�~
		return Collision::Check(transform1, this, transform2, collider2);
	}

#ifdef _DEBUG
	// �`��
	virtual void Draw(const Transform& transform) const override
	{
		DrawBox(
			static_cast<int>(transform.position.x + offset.x * transform.scale - size.x * transform.scale / 2),
			static_cast<int>(transform.position.y + offset.y * transform.scale - size.y * transform.scale / 2),
			static_cast<int>(transform.position.x + offset.x * transform.scale + size.x * transform.scale / 2),
			static_cast<int>(transform.position.y + offset.y * transform.scale + size.y * transform.scale / 2),
			GetColor(0, 255, 0), false
		);
	}
#endif
};
