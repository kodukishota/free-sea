#pragma once
#include"Vector3.h"
#include"NavMesh.h"
#include"DxLib.h"

class CheckRoot
{
private:
	// �o�H�T���Ŏg�p�������ۑ�
	Vector3 m_startPos;	// �T���J�n�ʒu
	Vector3 m_endPos;	// �T���ڕW�ʒu
	PathPlanUnit* m_unitArray;	// �S�|���S���̏��z�񂪊i�[���ꂽ�������̈�̐擪�A�h���X
	PathPlanUnit* m_activeFirst;	// �|���S���Q�̍ŏ��̃|���S�����ւ̃A�h���X
	PathPlanUnit* m_start;	// �T���̃X�^�[�g�n�_�ɂ���|���S�����ւ̃A�h���X
	PathPlanUnit* m_goal;	// �T���̖ڕW�n�_�ɂ���|���S�����ւ̃A�h���X

	// �ړ������p
	int m_nowPolyIndex;	// ���ݏ���Ă���|���S���ԍ�
	Vector3 m_nowPos;	// ���݈ʒu
	Vector3 m_moveDirection;	// �ړ�����
	PathPlanUnit* m_nowPathPlan;	// ���ݏ���Ă���|���S���̌o�H�T����񂪊i�[����Ă���A�h���X
	PathPlanUnit* m_targetPathPlan;	// ���̒��Ԓn�_�ɂȂ�o�H��̃|���S�����ւ̃A�h���X
	PathPlanUnit* m_pastPoly;	// 1�O�̃|���S�����
	NavMesh* m_navMesh;

public:
	CheckRoot(NavMesh* navMesh) :
		m_navMesh(navMesh),
		m_startPos(Vector3(0, 0, 0)),
		m_endPos(Vector3(0, 0, 0)),
		m_unitArray(nullptr),
		m_activeFirst(nullptr),
		m_start(nullptr),
		m_goal(nullptr),
		m_nowPolyIndex(0),
		m_nowPos(Vector3(0, 0, 0)),
		m_moveDirection(Vector3(0, 0, 0)),
		m_nowPathPlan(nullptr),
		m_targetPathPlan(nullptr),
		m_pastPoly(nullptr) {}

	// �w��̂Q�_�Ԃ𒼐��I�Ɉړ��ł��邩
	bool CheckPolyMove(Vector3 startPos, Vector3 goalPos);

	// �w��̂Q�_�Ԃ𒼐��I�Ɉړ��ł��邩�i���w��Łj
	bool CheckPolyMoveWidth(Vector3 startPos, Vector3 goalPos, float width);

	// �w��̂Q�_�Ԃ��o�H�T��
	bool SetPathPlan(Vector3 startPos, Vector3 goalPos, int* polyCount, bool* found);

	// �o�H�T�������폜
	void RemovePathPlan();

	// �T���o�H�̈ړ������̏�����
	void MoveInitialize(const Vector3& pos);

	// �T���o�H�̈ړ�����
	Vector3 Move(const Vector3& pos, const float speed, const float width, int* polyCount);

	// �T���o�H�̈ړ��������X�V�itrue:�ڕW�n�_�ɓ��B, false:�ڕW�n�_�ɖ����B�j
	bool RefreshMoveDirection(const float speed, const float width, int* polyCount);

	// ���݂̃|���S���Ƀv���C���[�����邩�ǂ���
	bool CheckPlayerPoly(const Vector3& enemyPos, const Vector3& playerPos);
};