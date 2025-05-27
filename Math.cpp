#include"Math.h"
#include<math.h>

// 1�̒l����]�l�ɕϊ�����i�x�� -> ���W�A���j
float Math::DegtoRad(float value)
{
	return value * DX_PI_F / Pi;
}

// ���W�A�� -> �x���ɕϊ�
float Math::RadtoDeg(float rad)
{
	return rad * Pi / DX_PI_F;
}

// Vector3��Ԃ�(��]�l)
Vector3 Math::ChangeVec(const Vector3& v)
{
	VECTOR rot;
	rot = VGet(v.x * DX_PI_F / Pi, v.y * DX_PI_F / Pi, v.z * DX_PI_F / Pi);
	return Vector3(rot.x, rot.y, rot.z);
}

// �x�N�g���𐳋K������i�����x�N�g�������j
Vector3 Math::Normalized(const Vector3& rotate)
{
	float length = rotate.Magnitude();
	if (length == 0)
	{
		// ������0�̏ꍇ���K���ł��Ȃ��̂ŁA���̃x�N�g����Ԃ�
		return rotate;
	}
	return Vector3(rotate / length);
}

// �x�N�g������]������
Vector3 Math::RotateVec(const Vector3& v, const Quaternion& q)
{
	Quaternion v_q(v.x, v.y, v.z, 0);
	Quaternion qConj = q.Conjugate();
	Quaternion result = q * v_q * qConj;

	return Vector3(result.x, result.y, result.z);
}

// �x�N�g���̂Ȃ��p(XZ)���v�Z����
float Math::ACosPlane(const Vector3& v1, const Vector3& v2)
{
	Vector3 vec1 = Vector3(v1.x, 0, v1.z);
	Vector3 vec2 = Vector3(v2.x, 0, v2.z);
	// �x�N�g���̂Ȃ��p�icos�Ɓj���o��
	float cosSita = VDot(vec1, vec2) / (vec1.Magnitude() * vec2.Magnitude());
	// cosSita�̒l��-1�`1�Ɏ��܂�悤�ɐ���
	if (cosSita > 1.0f) cosSita = 1.0f;
	if (cosSita < -1.0f) cosSita = -1.0f;

	// ���W�A���ɕϊ�
	float sita = acosf(cosSita);

	// �O�ςŊp�x�̕����𔻒�
	Vector3 crossProduct = v1.CrossP(v2);
	if (crossProduct.y < 0)
	{
		// �O�ς�y���������̎��A�����v���i�p�x - 180�x�j
		//cosSita = 2.0f * DX_PI_F - cosSita;
		sita = 2.0f * DX_PI_F - sita;
	}

	// 0�`180�x�ŕԂ�
	return sita * Pi / DX_PI_F;
}

// �x�N�g���̂Ȃ��p(XYZ)���v�Z����
float Math::ACos(const Vector3& v1, const Vector3& v2)
{
	Vector3 vec1 = Vector3(v1.x, v1.y, v1.z);
	Vector3 vec2 = Vector3(v2.x, v2.y, v2.z);
	// �x�N�g���̂Ȃ��p�icos�Ɓj���o��
	float cosSita = VDot(vec1, vec2) / (vec1.Magnitude() * vec2.Magnitude());
	// cosSita�̒l��-1�`1�Ɏ��܂�悤�ɐ���
	if (cosSita > 1.0f) cosSita = 1.0f;
	if (cosSita < -1.0f) cosSita = -1.0f;

	// �O�ςŊp�x�̕����𔻒�
	Vector3 crossProduct = v1.CrossP(v2);
	if (crossProduct.z < 0)
	{
		// �O�ς�z���������̎��A�����v���i�p�x - 180�x�j
		cosSita = 2.0f * DX_PI_F - cosSita;
	}

	// ���W�A���ɕϊ�
	float sita = acosf(cosSita);

	// 0�`180�x�ŕԂ�
	return sita * Pi / DX_PI_F;
}

// �O���x�N�g������ɉ�]�s����쐬����
MATRIX Math::GetLookRotMat(const Vector3& forword, const Vector3& camFront)
{
	return MGetRotVec2(Normalized(forword), Normalized(camFront));
}

// �s����g�����x�N�g���̕ϊ�
Vector3 Math::TransformVec(const Vector3& v, const MATRIX mat)
{
	float x = v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + mat.m[3][0];
	float y = v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + mat.m[3][1];
	float z = v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + mat.m[3][2];
	return Vector3(x, y, z);
}

// �_�̉�]�iXZ���ʂ���]��������j
Vector3 Math::PointRotate(const Vector3& satellite, const Vector3& center, const float angle)
{
	float ox = satellite.x - center.x;
	float oz = satellite.z - center.z;

	return Vector3(
		ox * cos(angle) + oz * sin(angle) + center.x,
		satellite.y,
		-ox * sin(angle) + oz * cos(angle) + center.z
		);
}


void Math::MatchAngleSign(float& afterAngle, const Vector3& moveDir, Vector3& transformAngle)
{
	afterAngle = atan2f(moveDir.z, moveDir.x);
	// ���݂̊p�x�̐�Βl��������ς�����̐��̐�Βl��菬���������牽�����Ȃ�(0 => 180)
	if (std::abs(transformAngle.y) > Math::GetSign(Math::Pi / 2))
	{
		if (Math::GetSign(transformAngle.y) < Math::GetSign(afterAngle))
		{
			// - => +
			transformAngle.y += Math::DegtoRad(Math::Pi * 2);
		}
		else if (Math::GetSign(transformAngle.y) > Math::GetSign(afterAngle))
		{
			// + => -
			transformAngle.y -= Math::DegtoRad(Math::Pi * 2);
		}
	}
}
