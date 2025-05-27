#include "Collision.h"
#include "Vector2.h"
#include "Transform.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include <cmath>
using std::abs;
using std::powf;

bool Collision::Check(
	const Transform& transform1, const BoxCollider2D* box1,
	const Transform& transform2, const BoxCollider2D* box2)
{
	// �e��`�̒��S���W�ƃT�C�Y��p��
	Vector2 center1 = transform1.position + box1->offset * transform1.scale;
	Vector2 size1 = box1->size * transform1.scale;

	Vector2 center2 = transform2.position + box2->offset * transform2.scale;
	Vector2 size2 = box2->size * transform2.scale;

	// ���S���W���m�̋����ƁA�T�C�Y/2�̍��v���r
	// ������e���ōs��
	if (abs(center1.x - center2.x) <= (size1.x + size2.x) / 2
		&& abs(center1.y - center2.y) <= (size1.y + size2.y) / 2)
	{
		return true;
	}
	return false;
}

bool Collision::Check(
	const Transform& transform1, const BoxCollider2D* box,
	const Transform& transform2, const CircleCollider2D* circle)
{
	// ��`�̍���E�E���̍��W�A�~�̒��S���W�Ɣ��a��p��
	Vector2 boxTopLeft = transform1.position + box->offset * transform1.scale - box->size * transform1.scale / 2;
	Vector2 boxBottomRight = boxTopLeft + box->size * transform1.scale;

	Vector2 circlePos = transform2.position + circle->offset * transform2.scale;
	float circleRadius = circle->radius * transform2.scale;

	// ��`���~�̔��a���L�����͈͂ɁA�~�̒��S�_�����Ȃ�
	if (boxTopLeft.x - circleRadius > circlePos.x
		|| boxBottomRight.x + circleRadius < circlePos.x
		|| boxTopLeft.y - circleRadius > circlePos.y
		|| boxBottomRight.y + circleRadius < circlePos.y)
	{
		return false;
	}

	// ������g���e2��̒l��p��
	float left2Pow = powf(boxTopLeft.x - circlePos.x, 2);
	float right2Pow = powf(boxBottomRight.x - circlePos.x, 2);
	float top2Pow = powf(boxTopLeft.y - circlePos.y, 2);
	float bottom2Pow = powf(boxBottomRight.y - circlePos.y, 2);
	float radius2Pow = powf(circleRadius, 2);

	// ����̓����蔻��
	if (boxTopLeft.x > circlePos.x && boxTopLeft.y > circlePos.y
		&& !(left2Pow + top2Pow < radius2Pow))
	{
		return false;
	}

	// �E��̓����蔻��
	if (boxBottomRight.x < circlePos.x && boxTopLeft.y > circlePos.y
		&& !(right2Pow + top2Pow < radius2Pow))
	{
		return false;
	}

	// �����̓����蔻��
	if (boxTopLeft.x > circlePos.x && boxBottomRight.y < circlePos.y
		&& !(left2Pow + bottom2Pow < radius2Pow))
	{
		return false;
	}

	// �E���̓����蔻��
	if (boxBottomRight.x < circlePos.x && boxBottomRight.y < circlePos.y
		&& !(right2Pow + bottom2Pow < radius2Pow))
	{
		return false;
	}

	return true;
}

bool Collision::Check(
	const Transform& transform1, const CircleCollider2D* circle1,
	const Transform& transform2, const CircleCollider2D* circle2)
{
	// �e�~�̒��S���W�Ɣ��a��p��
	Vector2 center1 = transform1.position + circle1->offset * transform1.scale;
	float radius1 = circle1->radius * transform1.scale;

	Vector2 center2 = transform2.position + circle2->offset * transform2.scale;
	float radius2 = circle2->radius * transform2.scale;

	// ���S���W�̋����ƁA���a�̍��v���r
	if (powf(center2.x - center1.x, 2) + powf(center2.y - center1.y, 2) <= powf(radius1 + radius2, 2))
	{
		return true;
	}
	return false;
}
