#include"Quaternion.h"
#include"Math.h"
#include"Vector3.h"

// Vector3�ŗv�f���w��
constexpr Quaternion::Quaternion(const Vector3& v) :
	x(static_cast<float>(v.x)),
	y(static_cast<float>(v.y)),
	z(static_cast<float>(v.z)),
	w(static_cast<float>(0)) {}

// �x�N�g���ւ̃L���X�g
Quaternion::operator Vector3() const
{
	return Vector3(x, y, z);
}

// �s��ւ̕ϊ�
Quaternion::operator DxLib::MATRIX() const
{
	float xx2 = 2 * x * x;
	float yy2 = 2 * y * y;
	float zz2 = 2 * z * z;
	float xy2 = 2 * x * y;
	float xz2 = 2 * x * z;
	float yz2 = 2 * y * z;
	float wx2 = 2 * w * x;
	float wy2 = 2 * w * y;
	float wz2 = 2 * w * z;

	// �s��ɕϊ�
	MATRIX m;
	m.m[0][0] = 1 - yy2 - zz2;
	m.m[0][1] = xy2 + wz2;
	m.m[0][2] = xz2 - yz2;
	m.m[0][3] = 0;
	m.m[1][0] = xy2 - wz2;
	m.m[1][1] = 1 - xx2 - zz2;
	m.m[1][2] = yz2 + wx2;
	m.m[1][3] = 0;
	m.m[2][0] = xz2 + wy2;
	m.m[2][1] = yz2 - wx2;
	m.m[2][2] = 1 - xx2 - yy2;
	m.m[2][3] = 0;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;

	return m;
}

// �x�N�g������]������
Vector3 Quaternion::RotateVec(const Vector3& v, const Quaternion& q)
{
	return static_cast<Vector3>(q.Conjugate() * Quaternion(v));
}

// �C�ӎ���]�̎l�����̍쐬
Quaternion Quaternion::CreateRotationAxis(const Vector3& axis, const float angle)
{
	Vector3 v = Math::Normalized(axis);
	return Quaternion(
		v.x * std::sin(angle / 2), 
		v.y * std::sin(angle / 2),
		v.z * sin(angle / 2),
		std::cos(angle / 2)
	);
}

// ������ύX���邽�߂ɉ�]�̎l�������쐬�ifrom => to�j
Quaternion Quaternion::CreateRotateDirection(const Vector3& from, const Vector3& to)
{
	// ����������
	if (from / from.Magnitude() == to / to.Magnitude())
	{
		return CreateIdentity();
	}
	else
	{
		return CreateRotationAxis(from.CrossP(to), Math::ACos(from, to));
	}
}

// ����
float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
{
	return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

// �w�肵�����f���̉�]�iY���j
void Quaternion::RotateAxisY(const int model, const float rotAngle, const Vector3& pos)
{
	MATRIX m = MGetIdent();
	m = MMult(m, MGetRotY(-rotAngle + Math::RadtoDeg(Math::Pi / 2)));
	m = MMult(m, MGetTranslate(pos));
	MV1SetMatrix(model, m);
}

// �w�肵�����f���̉�]�i�㉺���]��������ԁj
void Quaternion::RotateAxisYZ(const int model, const float rotAngle, const Vector3& pos)
{
	MATRIX m = MGetIdent();
	m = MMult(m, MGetRotZ(Math::DegtoRad(180)));
	m = MMult(m, MGetRotY(-rotAngle + Math::RadtoDeg(Math::Pi / 2)));
	m = MMult(m, MGetTranslate(pos));
	MV1SetMatrix(model, m);
}

