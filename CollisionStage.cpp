#include"CollisionStage.h"
#include"LoadPlayer.h"

// �X�e�[�W�̓����蔻����쐬
CollisionStage::CollisionStage(const char* floorModelPath, const char* wallModelPath, const Vector3& pos) :
	m_cap1(Vector3(0, 0, 0))
{
	// �X�e�[�W�̓ǂݍ���
	// ��
	m_modelFloor = MV1LoadModel(floorModelPath);
	// ��
	m_modelWall = MV1LoadModel(wallModelPath);

	// ���W������
	MV1SetPosition(m_modelFloor, Vector3(0, 0, 0));
	MV1SetPosition(m_modelWall, Vector3(0, 0, 0));

	// ���f���S�̂̃R���W���������\�z
	// ��
	MV1SetupCollInfo(m_modelFloor, -1, 8, 8, 8);
	MV1SetupReferenceMesh(m_modelFloor, -1, true);
	// ��
	MV1SetupCollInfo(m_modelWall, -1, 8, 8, 8);
	MV1SetupReferenceMesh(m_modelWall, -1, true);

#ifdef _DEBUG
	m_refPolyFloor = MV1GetReferenceMesh(m_modelFloor, -1, true);
	m_refPolyWall = MV1GetReferenceMesh(m_modelWall, -1, true);
#endif // _DEBUG

	// ���C�̐ݒ�
	m_checkMoveStart = Vector3(0, 0, 0);
	m_checkMoveEnd = Vector3(0, 0, 0) - CheckLineLength;

	m_getHeightStart = Vector3(0, 0, 0) + DiffGetLine;
	m_getHeightEnd = Vector3(0, 0, 0);

	// �\���̂̏�����
	m_stagePoly = MV1CollCheck_Line(m_modelFloor, -1, m_checkMoveStart, m_checkMoveEnd);
	m_polyHeight = MV1CollCheck_Line(m_modelFloor, -1, m_getHeightStart, m_getHeightEnd);
}

void CollisionStage::Release()
{
	MV1DeleteModel(m_modelFloor);
	MV1DeleteModel(m_modelWall);
}

// �ړ��\���ɑ��ꂪ���邩�ǂ���
int CollisionStage::CheckStage(const Vector3& pos)
{
	m_checkMoveStart = pos + DeffRay;
	m_checkMoveEnd = pos - CheckLineLength;

	// ���f���Ɛ����i�v���C���[�j�Ƃ̓����蔻��
	m_stagePoly = MV1CollCheck_Line(m_modelFloor, -1, m_checkMoveStart, m_checkMoveEnd);

	return m_stagePoly.HitFlag;
}

// �v���C���[�̑����܂ł̃��C
MV1_COLL_RESULT_POLY CollisionStage::GetHeight(const Vector3& pos)
{
	m_getHeightStart = pos + DiffGetLine;
	m_getHeightEnd = pos;
	m_getHeightEnd.y -= 1;

	m_polyHeight = MV1CollCheck_Line(m_modelFloor, -1, m_getHeightStart, m_getHeightEnd);

	return m_polyHeight;
}

// �J���������܂�Ȃ��悤����
MV1_COLL_RESULT_POLY_DIM CollisionStage::CheckCamHitWall(Vector3 camPos, Vector3 camDir)
{
	// �����蔻��̌��ʂ��폜
	MV1CollResultPolyDimTerminate(m_camFrontPoly);

	Vector3 camTargetPos = camPos + (camDir * 2.0f);

	m_camFrontPoly = MV1CollCheck_LineDim(m_modelWall, -1, camPos, camTargetPos);

	if (m_camFrontPoly.HitNum > 0)
	{
		int i = 0;
	}

	return m_camFrontPoly;
}

// �v���C���[�̃J�v�Z���ƃX�e�[�W�̓����蔻����Ƃ�(�J�v�Z���ƃ��f���̓��������|���S����)
int CollisionStage::CapsuleCollider(const Vector3& pos)
{
	// �����蔻��̌��ʂ��폜
	MV1CollResultPolyDimTerminate(m_spherePoly);

	// �ǂƂ̓����蔻������Ŏ��i�K�N���̂ŏC���\��j
	m_cap1 = pos;
	m_spherePoly = MV1CollCheck_Sphere(m_modelWall, -1, Vector3(pos.x, pos.y + 100, pos.z), Radius);

	return m_spherePoly.HitNum;
}

// �w��̍��W�̒����A�Ⴕ���͒���ɂ���|���S���̔ԍ����擾����
int CollisionStage::CheckOnPolyIndex(const Vector3& pos, const MV1_REF_POLYGONLIST& polyList)
{
	Vector3 linePos1;
	Vector3 linePos2;
	HITRESULT_LINE hitRes;
	MV1_REF_POLYGON* refPoly;

	// �w����W��Y�������ɑ傫���L�т�������Z�b�g
	linePos1 = Vector3(pos.x, 1400.0f, pos.z);
	linePos2 = Vector3(pos.x, -1400.0f, pos.z);

	// �X�e�[�W���f���̃|���S���������J��Ԃ�
	refPoly = polyList.Polygons;
	for (int i = 0; i < polyList.PolygonNum; i++, refPoly++)
	{
		// �����Ɛڂ���|���S����Ԃ�
		hitRes = HitCheck_Line_Triangle(
			linePos1,
			linePos2,
			polyList.Vertexs[refPoly->VIndex[0]].Position,
			polyList.Vertexs[refPoly->VIndex[1]].Position,
			polyList.Vertexs[refPoly->VIndex[2]].Position
		);

		if (hitRes.HitFlag) return i;
	}

	// �|���S���������ꍇ
	return -1;
}

void CollisionStage::Draw()
{

#ifdef _DEBUG
	//MV1DrawModel(m_model);
	// �|���S���̐������J��Ԃ�
	for (int i = 0; i < m_refPolyFloor.PolygonNum; i++)
	{
		// �|���S�����`������O���_���g�p���ă��C���[�t���[����`�悷��
		DrawLine3D(
			m_refPolyFloor.Vertexs[m_refPolyFloor.Polygons[i].VIndex[0]].Position,
			m_refPolyFloor.Vertexs[m_refPolyFloor.Polygons[i].VIndex[1]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			m_refPolyFloor.Vertexs[m_refPolyFloor.Polygons[i].VIndex[1]].Position,
			m_refPolyFloor.Vertexs[m_refPolyFloor.Polygons[i].VIndex[2]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			m_refPolyFloor.Vertexs[m_refPolyFloor.Polygons[i].VIndex[2]].Position,
			m_refPolyFloor.Vertexs[m_refPolyFloor.Polygons[i].VIndex[0]].Position,
			GetColor(255, 255, 0));
	}

	// �|���S���̐������J��Ԃ�
	for (int i = 0; i < m_refPolyWall.PolygonNum; i++)
	{
		// �|���S�����`������O���_���g�p���ă��C���[�t���[����`�悷��
		DrawLine3D(
			m_refPolyWall.Vertexs[m_refPolyWall.Polygons[i].VIndex[0]].Position,
			m_refPolyWall.Vertexs[m_refPolyWall.Polygons[i].VIndex[1]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			m_refPolyWall.Vertexs[m_refPolyWall.Polygons[i].VIndex[1]].Position,
			m_refPolyWall.Vertexs[m_refPolyWall.Polygons[i].VIndex[2]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			m_refPolyWall.Vertexs[m_refPolyWall.Polygons[i].VIndex[2]].Position,
			m_refPolyWall.Vertexs[m_refPolyWall.Polygons[i].VIndex[0]].Position,
			GetColor(255, 255, 0));
	}

	//DrawCapsule3D(m_cap1, m_cap2, Radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);

	Vector3 pos = m_cap1;
	DrawSphere3D(Vector3(pos.x, pos.y + 100, pos.z), Radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
#endif // DEBUG
}
