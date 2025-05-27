#pragma once
#include"Vector3.h"

class Transform3D;
class BoxCollider3D;

class Collision3D
{
public:
	// ���Ɣ�
	static bool Check(
		const Transform3D& transform1, const BoxCollider3D* box1,
		const Transform3D& transform2, const BoxCollider3D* box2
	);

	// �������ɓ��e���ꂽ���������瓊�e�����̒������o��(sep:������, e1,2,3:���葊��̊e�����x�N�g��)
	static float GetLengthSeparateAxis(
		const Vector3& sep,
		const Vector3& e1,
		const Vector3& e2,
		const Vector3& e3 = Vector3(0, 0, 0)
	);
};