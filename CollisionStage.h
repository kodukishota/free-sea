#pragma once
#pragma once
#include"Node.h"
#include"Vector3.h"
#include"DxLib.h"

class CollisionStage : public Node
{
private:
	static constexpr Vector3 DeffRay = Vector3(0, 100, 0);	// ����m�F�p�̃��C��̓��ɂ߂荞�܂��钷��
	static constexpr Vector3 CheckLineLength = Vector3(0, 3000, 0);	// ���ꂪ���邩�ǂ������m�F���郌�C�̒���
	static constexpr Vector3 DiffGetLine = Vector3(0, 60, 0);	// �v���C���[�̑����܂ł̃��C�̒���
	static constexpr Vector3 ModelHeight = Vector3(0, 180, 0);		// �g�p���Ă��郂�f���̍���
	static constexpr float Radius = 60.0f;		// �J�v�Z���Ɏg�����̔��a
	static constexpr float CapsuleLength = 180.0f;	// �J�v�Z���̒����i�����m�̋����j
	static constexpr float DiffCapsule = 10.0f;	// �J�v�Z���������Ɠ���̔�����Ƃ�Ȃ����߂̍���

	int m_modelFloor;	// �����f���n���h��
	int m_modelWall;	// �ǃ��f���n���h��
	MV1_COLL_RESULT_POLY m_stagePoly;	// ���C�̐�ɂ��郁�b�V���̏��
	MV1_COLL_RESULT_POLY m_polyHeight;	// ���C�̐�ɂ��郁�b�V���̏��
	MV1_COLL_RESULT_POLY_DIM m_camFrontPoly;	// ���C�̐�ɂ��郁�b�V���̏��i�J�����p�j
	MV1_REF_POLYGONLIST m_refPolyFloor;	// �X�e�[�W���f���S�̂̎Q�Ɨp���b�V�����i���j
	MV1_REF_POLYGONLIST m_refPolyWall;	// �X�e�[�W���f���S�̂̎Q�Ɨp���b�V�����i�ǁj

	MV1_COLL_RESULT_POLY_DIM m_spherePoly;	// ���̓����蔻��

	// �ړ��\�͈͂̃`�F�b�N�p(�v���C���[�̑�����艺�ɒ���)
	Vector3 m_checkMoveStart;
	Vector3 m_checkMoveEnd;

	// ������t�B�[���h�̍����擾�p�i�v���C���[�̑����܂ł̒����j
	Vector3 m_getHeightStart;
	Vector3 m_getHeightEnd;

	// �f�o�b�O�p
	Vector3 m_cap1;

protected:
	virtual void Release() override;	// ���\�[�X�̉��
	virtual void Draw() override;

public:
	CollisionStage(const char* floorModelPath, const char* wallModelPath, const Vector3& pos);

	// �ړ��\���ɑ��ꂪ���邩�ǂ���
	int CheckStage(const Vector3& pos);

	// �v���C���[�̑����܂ł̃��C(�\���̂�Ԃ�)
	MV1_COLL_RESULT_POLY GetHeight(const Vector3& pos);

	// �J�����̕`�拗���𒲐�����p
	MV1_COLL_RESULT_POLY_DIM CheckCamHitWall(Vector3 camPos, Vector3 camTargetPos);

	// �v���C���[�̃J�v�Z���ƃX�e�[�W�̓����蔻����Ƃ�
	int CapsuleCollider(const Vector3& pos);

	// �g�p���Ă��郌�C�̒������擾�i���]��Ԃ�y���W�擾�p�j
	Vector3 RayLength()
	{
		return DiffGetLine;
	}

	// ���̃��b�V�����f�����擾
	int GetMeshModel()
	{
		return m_modelFloor;
	}

	// ���ƃX�e�[�W�̕ǂ̓����蔻����
	MV1_COLL_RESULT_POLY_DIM GetColSphere()
	{
		return m_spherePoly;
	}

	// �J�����p�����ƕǂ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM GetColCamLine()
	{
		return m_camFrontPoly;
	}

	// �w��̍��W�̒����A�Ⴕ���͒���ɂ���|���S���̔ԍ����擾����
	int CheckOnPolyIndex(const Vector3& pos, const MV1_REF_POLYGONLIST& polyList);
};