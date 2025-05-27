#pragma once
#include "Collider.h"
#include "Collision.h"
#include "DxLib.h"

class CircleCollider2D : public Collider
{
public:
	int radius;	// ���a

	// �R���X�g���N�^
	CircleCollider2D(int radius, const Vector2& offset = Vector2(0, 0)) :
		Collider(offset),
		radius(radius) {}

	// �Փ˔���
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collider2) const override
	{
		// �_�u���f�B�X�p�b�`�ɂ��`�󎯕ʂ�����
		return collider2->CheckCollision(transform2, transform1, this);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider2D* collider2) const override
	{
		// ��`�~�~
		return Collision::Check(transform2, collider2, transform1, this);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider2D* collider2) const override
	{
		// �~�~�~
		return Collision::Check(transform1, this, transform2, collider2);
	}

#ifdef _DEBUG
	// �`��
	virtual void Draw(const Transform& transform) const override
	{
		DrawCircle(
			static_cast<int>(transform.position.x + offset.x * transform.scale),
			static_cast<int>(transform.position.y + offset.y * transform.scale),
			static_cast<int>(radius * transform.scale),
			GetColor(0, 255, 0), false
		);
	}
#endif
};
