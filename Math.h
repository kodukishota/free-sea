#pragma once
#include"Vector3.h"
#include"Quaternion.h"

class Math
{
private:


public:
	static constexpr float Pi = 180.0f;	// ��

	// 1�̒l����]�l�ɕϊ�����i�x�� -> ���W�A���j
	static float DegtoRad(float value);

	// ���W�A�� -> �x���ɕϊ�
	static float RadtoDeg(float rad);

	// VECTOR��Ԃ�(��]�l)
	static Vector3 ChangeVec(const Vector3& v);

	// �x�N�g���𐳋K������i�����x�N�g�������j
	static Vector3 Normalized(const Vector3& rotate);

	// �x�N�g������]������
	static Vector3 RotateVec(const Vector3& v, const Quaternion& q);

	// �x�N�g���̂Ȃ��p���v�Z����(XZ����)
	static float ACosPlane(const Vector3& v1, const Vector3& v2);
	
	// �x�N�g���̂Ȃ��p���v�Z����
	static float ACos(const Vector3& v1, const Vector3& v2);

	// �O���x�N�g������ɉ�]�s����쐬����
	static MATRIX GetLookRotMat(const Vector3& forword, const Vector3& camFront);

	// �s����g�����x�N�g���̕ϊ�
	static Vector3 TransformVec(const Vector3& v, const MATRIX mat);

	// �_�̉�]
	static Vector3 PointRotate(const Vector3& satellite, const Vector3& center, const float angle);

	// ����������Ă���
	template<typename T>
	static int GetSign(T v)
	{
		return (v > 0) - (v < 0);
	}

	// ��]�Ō��݂̌����Ɖ�]�\��̌����̕������Ⴄ�Ƃ��ɕ��������킹��i180 �` -180�ł������Ȃ����߁j
	static void MatchAngleSign(float& afterAngle, const Vector3& moveDir, Vector3& transformAngle);
};
