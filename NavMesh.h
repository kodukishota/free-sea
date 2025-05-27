#pragma once
#include"Vector3.h"
#include"DxLib.h"

// �|���S�����m�̘A�����
struct PolyLinkInfo
{
	int linkPolyIndex[3];	// �|���S����3�̕ӂƗאڂ��Ă���|���S���ԍ�(-1:�אڂȂ�, ����ȊO:�|���S���ԍ�)
	float linkPolyDistance[3];	// �אڂ��Ă���|���S���Ƃ̋���
	Vector3 centerPos;	// �|���S���̒��S���W
};

// �P�|���S���̏��
struct PathPlanUnit
{
	int polyIndex;	// �|���S���ԍ�
	float totalDistance;	// �|���S���ɓ��B����܂łɒʉ߂����|���S���Ԃ̋����̍��v
	int prevPolyIndex;	// �m�肵�Ă���P�O�̃|���S���i�|���S�����Ȃ��Ƃ���-1�j
	int nextPolyIndex;	// �m�肵�Ă���P��̃|���S���i�|���S�����Ȃ��Ƃ���-1�j
	PathPlanUnit* activeNext;	// �o�H�T���Ώۂ̎��̃|���S���̃A�h���X���i�[
};

class CollisionStage;

class NavMesh
{
private:
	MV1_REF_POLYGONLIST m_polyList;	// �X�e�[�W�̃|���S�����
	PolyLinkInfo* m_polyLink;	// �X�e�[�W���f���̑S�|���S�����̘A����񂪊i�[���ꂽ�z��

	CollisionStage* m_collisionStage;

public:
	NavMesh(CollisionStage* collisionStage);

	// �w����W�̒����A����̃|���S���ԍ����擾�i�Ȃ��ꍇ��-1�j
	int CheckPolyIndex(Vector3 pos);

	// �|���S�����m�̘A�������쐬
	void SetPolyLinkInfo();

	// �|���S�����m�̘A�����̍폜
	void RemovePolyLinkInfo();

	// �|���S���̏����g���āA�|�W�V������Ԃ�
	Vector3 GetPos(const int polygonNum = 0);

	// �|���S���̘A�������擾
	PolyLinkInfo* GetPolyLinkInfo()
	{
		return m_polyLink;
	}

	// �|���S���̏����擾
	MV1_REF_POLYGONLIST GetPolyList()
	{
		return m_polyList;
	}
};
