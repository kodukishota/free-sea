#pragma once
#include "Vector2.h"
#include "Transform.h"

class BoxCollider2D;
class CircleCollider2D;

class Collider
{
public:
	// ���S���W����̃Y��
	Vector2 offset;

	// �R���X�g���N�^
	Collider(const Vector2& offset) :
		offset(offset) {}

	// �Փ˔���
	// �_�u���f�B�X�p�b�`�ɂ��`�󎯕ʂ��s��
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collider2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider2D* collider2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider2D* collider2) const = 0;

#ifdef _DEBUG
	// �`��
	virtual void Draw(const Transform& transform) const = 0;
#endif
};
