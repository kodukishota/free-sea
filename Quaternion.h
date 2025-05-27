#pragma once
#include<cmath>
#include"DxLib.h"

class Vector3;

class Quaternion
{
public:
	float x, y, z, w;
	// -----�R���X�g���N�^-----
	// �f�t�H���g
	Quaternion() :
		x(0),
		y(0),
		z(0),
		w(0){}

	// �e�v�f���w�肵�ď�����
	template<typename T1, typename T2, typename T3, typename T4>
	constexpr Quaternion(T1 x, T2 y, T3 z, T4 w) :
		x(static_cast<float>(x)),
		y(static_cast<float>(y)),
		z(static_cast<float>(z)),
		w(static_cast<float>(w)){}

	// Vector3�ŗv�f���w��
	constexpr Quaternion(const Vector3& v);

	// �x�N�g���ւ̃L���X�g
	operator Vector3() const;

	// �s��ւ̕ϊ�
	operator DxLib::MATRIX() const;

	// ���𕡑f�����擾
	constexpr Quaternion Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	// �����̂Q���Ԃ�
	constexpr float GetLengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	// ������Ԃ�
	float GetLength() const
	{
		return std::sqrt(GetLengthSquared());
	}

	// ���K������
	void Normalized()
	{
		float l = GetLength();

		x /= l;
		y /= l;
		z /= l;
		w /= l;
	}

	// ----���Z�q�I�y���[�^----
	// ���
	constexpr Quaternion operator =(const Quaternion& q) const
	{
		return q;
	}

	// ��Z
	constexpr Quaternion operator *(const Quaternion& q) const
	{
		return	Quaternion(
			w * q.w - x * q.x - y * q.y - z * q.z,
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y - x * q.z + y * q.w + z * q.x,
			w * q.z + x * q.y - y * q.x + z * q.w
		);
	}

	// ----�l�����̍쐬----
	// �P�ʎl�����̍쐬
	static Quaternion CreateIdentity()
	{
		return Quaternion(0, 0, 0, 1);
	}
	
	// �x�N�g������]������
	static Vector3 RotateVec(const Vector3& v, const Quaternion& q);

	// �C�ӎ���]�̎l�����̍쐬
	static Quaternion CreateRotationAxis(const Vector3& axis, const float angle);

	// ������ύX���邽�߂ɉ�]�̎l�������쐬�ifrom����to�ւ̊p�x�j
	static Quaternion CreateRotateDirection(const Vector3& from, const Vector3& to);

	// ----�l�����̐ݒ�----
	// �P�ʎl�����̐ݒ�
	void SetIdentity() const
	{
		*this = CreateIdentity();
	}

	// �C�ӎ���]�̎l�����̐ݒ�
	void SetRotateAxis(const Vector3& v, const float angle)
	{
		*this = CreateRotationAxis(v, angle);
	}

	// ������ύX���邽�߂̉�]�̎l�����ݒ�
	void SetRotationDirection(const Vector3& from, const Vector3& to)
	{
		*this = CreateRotateDirection(from, to);
	}

	// ����
	static float Dot(const Quaternion& q1, const Quaternion& q2);

	// �w�肵�����f���̉�]�iY���j
	static void RotateAxisY(const int model, const float rotAngle, const Vector3& pos);

	// �w�肵�����f���̉�]�i�㉺���]��������ԁj
	static void RotateAxisYZ(const int model, const float rotAngle, const Vector3& pos);
};