#include "Vector3.h"
#include "Vector2.h"
#include <cmath>

// Vector2�ւ̃L���X�g
Vector3::operator Vector2() const
{
	return Vector2(x, y);
}

// VECTOR(DxLib)�ւ̃L���X�g
Vector3::operator VECTOR() const
{
	return VECTOR(VGet(x, y, z));
}

// VECTOR_D(DxLib)�ւ̃L���X�g
Vector3::operator VECTOR_D() const
{
	return VECTOR_D(VGetD(static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)));
}

// �������擾
float Vector3::Magnitude() const
{
	return std::sqrtf(SqrMagnitude());
}
