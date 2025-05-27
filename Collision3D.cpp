#include"Collision3D.h"
#include"Vector3.h"
#include"Transform3D.h"
#include"BoxCollider3D.h"
#include<math.h>

// ���Ɣ�
bool Collision3D::Check(
	const Transform3D& transform1, const BoxCollider3D* box1,
	const Transform3D& transform2, const BoxCollider3D* box2
)
{
	// �e���̒��S���W�ƃT�C�Y��p�ӁA�I�u�W�F�N�g�̉�]���v�Z����(��]�͖�����)
	Vector3 center1 = transform1.position + box1->m_offset.ChangeScale(transform1.scale);
	Vector3 vecX1 = (box1->m_normVec[0] * box1->m_size.x) / 2;
	Vector3 vecY1 = (box1->m_normVec[1] * box1->m_size.y) / 2;
	Vector3 vecZ1 = (box1->m_normVec[2] * box1->m_size.z) / 2;

	Vector3 center2 = transform2.position + box2->m_offset.ChangeScale(transform2.scale);
	Vector3 vecX2 = (box2->m_normVec[0] * box2->m_size.x) / 2;
	Vector3 vecY2 = (box2->m_normVec[1] * box2->m_size.y) / 2;
	Vector3 vecZ2 = (box2->m_normVec[2] * box2->m_size.z) / 2;

	// box1�̒��S->box2�̒��S�̃x�N�g��
	Vector3 distance = center1 - center2;

	// �������ʂ����݂��Ă��邩�𔻒� �i�����ꂩ�̏����ɓ��Ă͂܂������A�Փ˂͂��Ă��Ȃ��j
	// ---- �e�W���������x�N�g�� ----
	// ������ box1X
	float r1 = vecX1.Magnitude();
	float r2 = GetLengthSeparateAxis(box1->m_normVec[0], vecX2, vecY2, vecZ2);
	float length = static_cast<float>(fabs(distance.DotP(box1->m_normVec[0])));
	if (length > r1 + r2) return false;	

	// ������ box1Y
	r1 = vecY1.Magnitude();
	r2 = GetLengthSeparateAxis(box1->m_normVec[1], vecX2, vecY2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(box1->m_normVec[1])));
	if (length > r1 + r2) return false;

	// ������ box1Z
	r1 = vecZ1.Magnitude();
	r2 = GetLengthSeparateAxis(box1->m_normVec[2], vecX2, vecY2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(box1->m_normVec[2])));
	if (length > r1 + r2) return false;

	// ������ box2X
	r1 = vecX2.Magnitude();
	r2 = GetLengthSeparateAxis(box2->m_normVec[0], vecX1, vecY1, vecZ1);
	length = static_cast<float>(fabs(distance.DotP(box2->m_normVec[0])));
	if (length > r1 + r2) return false;

	// ������ box1Y
	r1 = vecY2.Magnitude();
	r2 = GetLengthSeparateAxis(box2->m_normVec[1], vecX1, vecY1, vecZ1);
	length = static_cast<float>(fabs(distance.DotP(box2->m_normVec[1])));
	if (length > r1 + r2) return false;

	// ������ box1Z
	r1 = vecZ2.Magnitude();
	r2 = GetLengthSeparateAxis(box2->m_normVec[2], vecX1, vecY1, vecZ1);
	length = static_cast<float>(fabs(distance.DotP(box2->m_normVec[2])));
	if (length > r1 + r2) return false;

	// ---- �o���̕����x�N�g���ɐ����ȕ����� ----
	// ������ box1X - box2X
	Vector3 cross = box1->m_normVec[0].CrossP(box2->m_normVec[0]);
	r1 = GetLengthSeparateAxis(cross, vecY1, vecZ1);
	r2 = GetLengthSeparateAxis(cross, vecY2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;
	// ������ box1X - box2Y
	cross = box1->m_normVec[0].CrossP(box2->m_normVec[1]);
	r1 = GetLengthSeparateAxis(cross, vecY1, vecZ1);
	r2 = GetLengthSeparateAxis(cross, vecX2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;
	// ������ box1X - box2Z
	cross = box1->m_normVec[0].CrossP(box2->m_normVec[2]);
	r1 = GetLengthSeparateAxis(cross, vecY1, vecZ1);
	r2 = GetLengthSeparateAxis(cross, vecX2, vecY2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;


	// ������ box1Y - box2X
	cross = box1->m_normVec[1].CrossP(box2->m_normVec[0]);
	r1 = GetLengthSeparateAxis(cross, vecX1, vecZ1);
	r2 = GetLengthSeparateAxis(cross, vecY2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;
	// ������ box1Y - box2Y
	cross = box1->m_normVec[1].CrossP(box2->m_normVec[1]);
	r1 = GetLengthSeparateAxis(cross, vecX1, vecZ1);
	r2 = GetLengthSeparateAxis(cross, vecX2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;
	// ������ box1Y - box2Z
	cross = box1->m_normVec[1].CrossP(box2->m_normVec[2]);
	r1 = GetLengthSeparateAxis(cross, vecX1, vecZ1);
	r2 = GetLengthSeparateAxis(cross, vecX2, vecY2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;


	// ������ box1Z - box2X
	cross = box1->m_normVec[2].CrossP(box2->m_normVec[0]);
	r1 = GetLengthSeparateAxis(cross, vecX1, vecY1);
	r2 = GetLengthSeparateAxis(cross, vecY2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;
	// ������ box1Z - box2Y
	cross = box1->m_normVec[2].CrossP(box2->m_normVec[1]);
	r1 = GetLengthSeparateAxis(cross, vecX1, vecY1);
	r2 = GetLengthSeparateAxis(cross, vecX2, vecZ2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;
	// ������ box1Z - box2Z
	cross = box1->m_normVec[2].CrossP(box2->m_normVec[2]);
	r1 = GetLengthSeparateAxis(cross, vecX1, vecY1);
	r2 = GetLengthSeparateAxis(cross, vecX2, vecY2);
	length = static_cast<float>(fabs(distance.DotP(cross)));
	if (length > r1 + r2) return false;

	// �������ʂ����݂��Ă��Ȃ��̂ŏՓ˂��Ă���
	return true;
}

// �������ɓ��e���ꂽ���������瓊�e�����̒������o��(sep:�W�������ꂽ������, e1�`3:���葊��̊e�����x�N�g��)
float Collision3D::GetLengthSeparateAxis(
	const Vector3& sep,
	const Vector3& e1,
	const Vector3& e2,
	const Vector3& e3
)
{
	// �������Ƃ��ꂼ��̎������̓��ς̘a(fabs:���������_�^�̐�Βl�����߂�, abs:�����^�̐�Βl�����߂�)
	float r1 = static_cast<float>(fabs(sep.DotP(e1)));
	float r2 = static_cast<float>(fabs(sep.DotP(e2)));
	float r3 = e3 != Vector3(0, 0, 0) ? static_cast<float>(fabs(sep.DotP(e3))) : 0;
	return r1 + r2 + r3;
}