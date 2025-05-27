#include"CheckRoot.h"
#include"Math.h"

// �w��̂Q�_�Ԃ𒼐��I�Ɉړ��ł��邩�i�A�������g�p����j
bool CheckRoot::CheckPolyMove(Vector3 startPos, Vector3 goalPos)
{
	int startPoly;
	int goalPoly;
	PolyLinkInfo* polyInfoStart;
	PolyLinkInfo* polyInfoGoal;
	Vector3 firstPos;
	Vector3 targetPos;
	Vector3 polyPos[3] = { Vector3(0, 0, 0) };
	int checkPoly[3] = { 0 };
	int checkPolyPrev[3] = { 0 };
	int checkPolyNum;
	int checkPolyPrevNum;
	int nextCheckPoly[3] = { 0 };
	int nextCheckPolyPrev[3] = { 0 };
	int nextCheckPolyNum;
	int nextCheckPolyPrevNum;
	int num;

	// �J�n���W�ƖڕW���W��Y��0�ɂ��ĕ��ʏ�̔�����s��
	startPos.y = 0;
	goalPos.y = 0;

	firstPos = startPos;
	targetPos = goalPos;

	// �J�n���W�ƖڕW���W�̐^���̃|���S���𒲂ׂ�
	startPoly = m_navMesh->CheckPolyIndex(startPos);
	goalPoly = m_navMesh->CheckPolyIndex(goalPos);

	// �|���S�������݂��Ȃ��ꍇ
	if (startPoly == -1 || goalPoly == -1) return false;

	// �J�n���W�ƖڕW���W�̒��� or �����̃|���S����o�^
	polyInfoStart = &m_navMesh->GetPolyLinkInfo()[startPoly];
	polyInfoGoal = &m_navMesh->GetPolyLinkInfo()[goalPoly];


	// �w�肵��������ɂ��邩�𔻒f���邽�߂̃|���S����o�^�i���� or �����j
	checkPolyNum = 1;
	checkPoly[0] = startPoly;
	checkPolyPrevNum = 0;
	checkPolyPrev[0] = -1;

	// ���ʂ��o��܂Ń��[�v
	while (true)
	{
		// ���̃��[�v�ł̃`�F�b�N�Ώۂ̃|���S���������Z�b�g
		nextCheckPolyNum = 0;

		// ���̃��[�v�Ń`�F�b�N�Ώۂ���O���|���S���������Z�b�g
		nextCheckPolyPrevNum = 0;

		if (checkPolyNum >= 4) checkPolyNum = 3;

		// �`�F�b�N�Ώۂ̃|���S�����������[�v
		for (int i = 0; i < checkPolyNum; i++)
		{
			// �`�F�b�N�Ώۂ̃|���S����3���W���擾
			polyPos[0] = VConvFtoD(m_navMesh->GetPolyList().Vertexs[m_navMesh->GetPolyList().Polygons[checkPoly[i]].VIndex[0]].Position);
			polyPos[1] = VConvFtoD(m_navMesh->GetPolyList().Vertexs[m_navMesh->GetPolyList().Polygons[checkPoly[i]].VIndex[1]].Position);
			polyPos[2] = VConvFtoD(m_navMesh->GetPolyList().Vertexs[m_navMesh->GetPolyList().Polygons[checkPoly[i]].VIndex[2]].Position);

			// y���W��0�ɂ��ĕ��ʔ�����s��
			polyPos[0].y = 0.0f;
			polyPos[1].y = 0.0f;
			polyPos[2].y = 0.0f;

			// �|���S���̒��_(0, 1)�ɗאڂ���|���S�������݂��� && �ӂ̐����ƈړ��J�n�_�A�I���_�Ō`������������ڂ��Ă���
			if (m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[0] != -1 &&
				Segment_Segment_MinLength_SquareD(firstPos, targetPos, polyPos[0], polyPos[1]) < 0.01
				)
			{
				if (m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[0] == goalPoly) return true;

				// �ӂƐڂ��Ă���|���S�������̃`�F�b�N�Ώۂɒǉ�
				for (num = 0; num < nextCheckPolyNum; num++)
				{
					// ���łɒǉ�����Ă���ꍇ�ǉ����Ȃ�
					if (nextCheckPoly[num] == m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[0]) break;
				}
				if (num == nextCheckPolyNum)
				{
					// ���̃��[�v�ŏ��O����|���S���̑Ώۂɉ�����
					for (num = 0; num < nextCheckPolyPrevNum; num++)
					{
						// ���łɒǉ�����Ă���ꍇ�ǉ����Ȃ�
						if (nextCheckPolyPrev[num] == checkPoly[i]) break;
					}
					if (num == nextCheckPolyPrevNum)
					{
						nextCheckPolyPrev[nextCheckPolyPrevNum] = checkPoly[i];
						nextCheckPolyPrevNum++;
					}

					// �P�O�̃��[�v�Ń`�F�b�N�ΏۂɂȂ����|���S���������Ȃ�
					for (num = 0; num < checkPolyPrevNum; num++)
					{
						if (checkPolyPrev[num] == m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[0]) break;
					}
					if (num == checkPolyPrevNum)
					{
						// �`�F�b�N�Ώۂɒǉ�
						nextCheckPoly[nextCheckPolyNum] = m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[0];
						nextCheckPolyNum++;
					}
				}
			}

			// �|���S���̒��_(1, 2)�ɗאڂ���|���S�������݂��� && �ӂ̐����ƈړ��J�n�_�A�I���_�Ō`������������ڂ��Ă���
			if (m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[1] != -1 &&
				Segment_Segment_MinLength_SquareD(firstPos, targetPos, polyPos[1], polyPos[2]) < 0.01
				)
			{
				if (m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[1] == goalPoly) return true;

				// �ӂƐڂ��Ă���|���S�������̃`�F�b�N�Ώۂɒǉ�
				for (num = 0; num < nextCheckPolyNum; num++)
				{
					// ���łɒǉ�����Ă���ꍇ�ǉ����Ȃ�
					if (nextCheckPoly[num] == m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[1]) break;
				}
				if (num == nextCheckPolyNum)
				{
					// ���̃��[�v�ŏ��O����|���S���̑Ώۂɉ�����
					for (num = 0; num < nextCheckPolyPrevNum; num++)
					{
						// ���łɒǉ�����Ă���ꍇ�ǉ����Ȃ�
						if (nextCheckPolyPrev[num] == checkPoly[i]) break;
					}
					if (num == nextCheckPolyPrevNum)
					{
						nextCheckPolyPrev[nextCheckPolyPrevNum] = checkPoly[i];
						nextCheckPolyPrevNum++;
					}

					// �P�O�̃��[�v�Ń`�F�b�N�ΏۂɂȂ����|���S���������Ȃ�
					for (num = 0; num < checkPolyPrevNum; num++)
					{
						if (checkPolyPrev[num] == m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[1]) break;
					}
					if (num == checkPolyPrevNum)
					{
						// �`�F�b�N�Ώۂɒǉ�
						nextCheckPoly[nextCheckPolyNum] = m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[1];
						nextCheckPolyNum++;
					}
				}
			}

			// �|���S���̒��_(2, 0)�ɗאڂ���|���S�������݂��� && �ӂ̐����ƈړ��J�n�_�A�I���_�Ō`������������ڂ��Ă���
			if (m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[2] != -1 &&
				Segment_Segment_MinLength_SquareD(firstPos, targetPos, polyPos[2], polyPos[0]) < 0.01
				)
			{
				if (m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[2] == goalPoly) return true;

				// �ӂƐڂ��Ă���|���S�������̃`�F�b�N�Ώۂɒǉ�
				for (num = 0; num < nextCheckPolyNum; num++)
				{
					// ���łɒǉ�����Ă���ꍇ�ǉ����Ȃ�
					if (nextCheckPoly[num] == m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[2]) break;
				}
				if (num == nextCheckPolyNum)
				{
					// ���̃��[�v�ŏ��O����|���S���̑Ώۂɉ�����
					for (num = 0; num < nextCheckPolyPrevNum; num++)
					{
						// ���łɒǉ�����Ă���ꍇ�ǉ����Ȃ�
						if (nextCheckPolyPrev[num] == checkPoly[i]) break;
					}
					if (num == nextCheckPolyPrevNum)
					{
						nextCheckPolyPrev[nextCheckPolyPrevNum] = checkPoly[i];
						nextCheckPolyPrevNum++;
					}

					// �P�O�̃��[�v�Ń`�F�b�N�ΏۂɂȂ����|���S���������Ȃ�
					for (num = 0; num < checkPolyPrevNum; num++)
					{
						if (checkPolyPrev[num] == m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[2]) break;
					}
					if (num == checkPolyPrevNum)
					{
						// �`�F�b�N�Ώۂɒǉ�
						nextCheckPoly[nextCheckPolyNum] = m_navMesh->GetPolyLinkInfo()[checkPoly[i]].linkPolyIndex[2];
						nextCheckPolyNum++;
					}
				}
			}
		}

		// ���̃��[�v�̃`�F�b�N�Ώۂ��Ȃ��Ƃ��A�����I�ȓ������ł��Ȃ�
		if (nextCheckPolyNum == 0) return false;

		// ���̃`�F�b�N�Ώۂ̃|���S�������R�s�[
		for (int i = 0; i < nextCheckPolyNum; i++)
		{
			if (i >= 3) break;
			checkPoly[i] = nextCheckPoly[i];
		}

		checkPolyNum = nextCheckPolyNum;

		// ���̃`�F�b�N�ΏۊO�ɂȂ�|���S�����R�s�[
		for (int i = 0; i < nextCheckPolyPrevNum; i++)
		{
			checkPolyPrev[i] = nextCheckPolyPrev[i];
		}

		checkPolyPrevNum = nextCheckPolyPrevNum;
	}

	return false;
}

// �w��̂Q�_�Ԃ𒼐��I�Ɉړ��ł��邩�i���w��Łj
bool CheckRoot::CheckPolyMoveWidth(Vector3 startPos, Vector3 goalPos, float width)
{
	Vector3 direction;
	Vector3 sideDirection;
	Vector3 tempVec;

	// �J�n���W����ڕW���W�ɒ����I�Ɉړ��ł��邩�`�F�b�N
	if (!CheckPolyMove(startPos, goalPos)) return false;

	// �J�n���W����ڕW���W�Ɍ������x�N�g�����Z�o
	direction = goalPos - startPos;

	// ���ʂȃx�N�g���ɕϊ�
	direction.y = 0;

	// �J�n���W����ڕW���W�ւ̃x�N�g���ɒ��p�Ȑ��K���x�N�g��
	sideDirection = direction.CrossP(Vector3(0, 1, 0));
	sideDirection = Math::Normalized(sideDirection);

	// �J�n���W�ƖڕW���W�𐂒�������width�̔����������炵�Ċm�F
	tempVec = sideDirection / (width / 2);
	if (!CheckPolyMove(startPos + tempVec, goalPos + tempVec)) return false;
	if (!CheckPolyMove(startPos - tempVec, goalPos - tempVec)) return false;

	// �w�蕝�������Ă������I�Ȉړ����\
	return true;
}

// �w��̂Q�_�Ԃ��o�H�T��
bool CheckRoot::SetPathPlan(Vector3 startPos, Vector3 goalPos, int* polyCount, bool* found)
{
	int num;
	int polyIndex;
	PathPlanUnit* pathUnit;
	PathPlanUnit* pathUnit_sub;
	PathPlanUnit* pathUnit_sub2;
	bool isGoal;
	// �S�[���܂ł̃|���S����
	int count = 0;

	// �X�^�[�g�ʒu�ƃS�[���ʒu��ۑ�
	m_startPos = startPos;
	m_endPos = goalPos;

	// �o�H�T���p�̃������m��
	m_unitArray = new PathPlanUnit[sizeof(PathPlanUnit) * m_navMesh->GetPolyList().PolygonNum];

	// �o�H�T���p�̃|���S���̏�����
	for (num = 0; num < m_navMesh->GetPolyList().PolygonNum; num++)
	{
		m_unitArray[num].polyIndex = num;
		m_unitArray[num].totalDistance = 0;
		m_unitArray[num].prevPolyIndex = -1;
		m_unitArray[num].nextPolyIndex = -1;
		m_unitArray[num].activeNext = nullptr;
	}

	// �X�^�[�g�n�_�̃|���S���ԍ����擾 -> �o�H�T���p�̍\���̂̃A�h���X��ۑ�
	polyIndex = m_navMesh->CheckPolyIndex(startPos);
	if (polyIndex == -1) return false;

	m_start = &m_unitArray[polyIndex];
	if (!m_start) return false;

	// �f�o�b�O�p
	if (!m_start)
	{
		m_start = &m_unitArray[polyIndex];
	}

	// �o�H�T���p�̃|���S���Ƃ��ăX�^�[�g�n�_�̃|���S����o�^
	m_activeFirst = &m_unitArray[polyIndex];

	// �S�[���n�_�ɂ���|���S���ԍ����擾 -> �o�H�T���p�̍\���̂̃A�h���X��ۑ�
	polyIndex = m_navMesh->CheckPolyIndex(goalPos);
	if (polyIndex == -1) return false;

	m_goal = &m_unitArray[polyIndex];
	if (!m_goal) return false;

	// �X�^�[�g�n�_�ƃS�[���n�_�̃|���S���������Ƃ�
	if (m_start == m_goal) return false;

	// �S�[���ɂ��ǂ蒅���܂ŒT��
	isGoal = false;
	while (!isGoal)
	{
		// �T���Ώۂ̃|���S��������
		pathUnit = m_activeFirst;
		m_activeFirst = nullptr;
		for (; pathUnit != nullptr; pathUnit = pathUnit->activeNext)
		{
			// �|���S���̕ӂ̐����J��Ԃ�
			for (num = 0; num < 3; num++)
			{
				// �אڂ���|���S�����Ȃ��Ƃ�
				if (m_navMesh->GetPolyLinkInfo()[pathUnit->polyIndex].linkPolyIndex[num] == -1) continue;

				// �אڂ���|���S�����o�H�T���������s���Ă��� && ��苗���̒����o�H  �������́@�X�^�[�g�n�_�̃|���S���̎�
				pathUnit_sub = &m_unitArray[m_navMesh->GetPolyLinkInfo()[pathUnit->polyIndex].linkPolyIndex[num]];
				if ((pathUnit_sub->prevPolyIndex != -1 && pathUnit_sub->totalDistance <= pathUnit->totalDistance + m_navMesh->GetPolyLinkInfo()[pathUnit->polyIndex].linkPolyDistance[num]) ||
					pathUnit_sub->polyIndex == m_start->polyIndex)
				{
					continue;
				}

				// �אڂ���|���S�����S�[���n�_�̎��A�S�[���t���O�𗧂Ă�
				if (pathUnit_sub->polyIndex == m_goal->polyIndex)
				{
					isGoal = true;
				}

				// �אڂ���|���S���Ɏ����̃|���S��������
				pathUnit_sub->prevPolyIndex = pathUnit->polyIndex;

				// �אڂ���|���S���ɂ����܂ł̋�������
				pathUnit_sub->totalDistance = pathUnit->totalDistance + m_navMesh->GetPolyLinkInfo()[pathUnit->polyIndex].linkPolyDistance[num];

				// ���̃��[�v�̒T���Ώۂ�ǉ�
				for (pathUnit_sub2 = m_activeFirst; pathUnit_sub2 != nullptr; pathUnit_sub2 = pathUnit_sub2->activeNext)
				{
					// ���łɒǉ�����Ă�����ǉ����Ȃ�
					if (pathUnit_sub2 == pathUnit_sub) break;
				}
				if (pathUnit_sub2 == nullptr)
				{
					pathUnit_sub->activeNext = m_activeFirst;
					m_activeFirst = pathUnit_sub;
				}
			}
		}

		// m_activeFirst == nullptr �̎��A�S�[���ɂ��ǂ蒅���Ȃ�
		if (m_activeFirst == nullptr) return false;

		count++;
	}

	// �S�[������X�^�[�g�܂ł��ǂ��āA�o�H��̎��Ɉړ�����ׂ��|���S���ԍ�����
	pathUnit = m_goal;
	do
	{
		pathUnit_sub = pathUnit;
		pathUnit = &m_unitArray[pathUnit_sub->prevPolyIndex];
		pathUnit->nextPolyIndex = pathUnit_sub->polyIndex;
	} while (pathUnit != m_start);

	if (count >= 15)
	{
		*polyCount = count / 2;
	}
	else if (count >= 2)
	{
		*polyCount = count;
	}
	else
	{
		*polyCount = 0;
	}

	// �T���I���t���O�𗧂Ă�
	*found = true;

	// �T���I��
	return true;
}

// �o�H�T�������폜
void CheckRoot::RemovePathPlan()
{
	// �o�H�T���ׂ̈Ɋm�ۂ����������̈�����
	delete[] m_unitArray;
	m_unitArray = nullptr;
}

// �T���o�H�̈ړ������̏�����
void CheckRoot::MoveInitialize(const Vector3& pos)
{
	// �ړ��J�n���ɏ���Ă���|���S�����X�^�[�g�n�_�ɐݒ�
	m_nowPolyIndex = m_start->polyIndex;

	// �ړ��J�n���_�̍��W�͌��݂̍��W
	m_nowPos = pos;

	// �ړ��J�n���̌o�H�T�������X�^�[�g�n�_�̃|���S�����ɂ���
	m_nowPathPlan = m_start;

	// �ړ��J�n���̈ړ����Ԓn�_�̌o�H�T�������X�^�[�g�n�_�̃|���S��
	m_targetPathPlan = m_start;

	// �ǂꂾ���|���S�����ړ����������J�E���g����p
	m_pastPoly = m_start;
}

// �T���o�H�̈ړ�����
Vector3 CheckRoot::Move(const Vector3& pos, const float speed, const float width, int* polyCount)
{
	// �ړ������̍X�V�A�S�[���ɂ��ǂ蒅���Ă�����I��
	if (RefreshMoveDirection(speed, width, polyCount)) return pos;

	// �ړ������̍��W�Ɉړ�
	m_nowPos += m_moveDirection * speed;

	// ���݂̍��W�ŏ���Ă���|���S��������
	m_nowPolyIndex = m_navMesh->CheckPolyIndex(m_nowPos);

	// ����Ă���|���S���̌o�H�T�������A�h���X�ɑ��
	m_nowPathPlan = &m_unitArray[m_nowPolyIndex];

	if (*polyCount != 0 && m_pastPoly != m_nowPathPlan)
	{
		// �ʒu�̍X�V
		m_pastPoly = m_nowPathPlan;
		*polyCount = *polyCount - 1;
	}

	return m_nowPos;
}

// �T���o�H�̈ړ��������X�V�itrue:�ڕW�n�_�ɓ��B, false:�ڕW�n�_�ɖ����B�j
bool CheckRoot::RefreshMoveDirection(const float speed, const float width, int* polyCount)
{
	PathPlanUnit* tempPathUnit;

	// ���ݏ���Ă���|���S�����S�[���n�_�̃|���S���̏ꍇ�A�����𕪊�
	if (m_nowPathPlan == m_goal)
	{
		// �����͖ڕW���W
		m_moveDirection = m_endPos - m_nowPos;
		m_moveDirection.y = 0.0f;

		// �ڕW���W�܂ł̋������ړ����x�ȉ��Ȃ瓞�B�����Ƃ���
		if (m_moveDirection.Magnitude() <= speed)
		{
			*polyCount = 0;
			return true;
		}

		m_moveDirection = Math::Normalized(m_moveDirection);

		return false;
	}

	// ���ݏ���Ă���|���S�����ړ����Ԓn�_�̏ꍇ�A���̒��Ԓn�_�����肷�鏈��������
	if (m_nowPathPlan == m_targetPathPlan)
	{
		// ���Ԓn�_�����܂�܂Ń��[�v
		while (true)
		{
			// �v���C���[���������Ȃ̂Œǂ�Ȃ�
			if (m_targetPathPlan->nextPolyIndex == 0) break;

			tempPathUnit = &m_unitArray[m_targetPathPlan->nextPolyIndex];

			// �o�H��̎��̃|���S���̒��S���W�ɒ����ړ��ł��Ȃ��Ƃ��A���[�v���甲����
			if (!CheckPolyMoveWidth(m_nowPos, m_navMesh->GetPolyLinkInfo()[tempPathUnit->polyIndex].centerPos, width)) break;

			// �`�F�b�N�Ώۂ��o�H��̍X�ɂP��̃|���S���ɕύX
			m_targetPathPlan = tempPathUnit;

			// �S�[���n�_�̃|���S���̎����[�v�𔲂���
			if (m_targetPathPlan == m_goal) break;
		}
	}

	// �ړ����������肷��i�ړ������͌��݂̍��W���璆�Ԓn�_�̃|���S���̒��S���W�Ɍ������j
	m_moveDirection = m_navMesh->GetPolyLinkInfo()[m_targetPathPlan->polyIndex].centerPos - m_nowPos;
	m_moveDirection.y = 0;
	m_moveDirection = Math::Normalized(m_moveDirection);

	// �S�[���ɂ��ǂ蒅���Ă��Ȃ�
	return false;
}

// ���݂̃|���S���Ƀv���C���[�����邩�ǂ���
bool CheckRoot::CheckPlayerPoly(const Vector3& enemyPos, const Vector3& playerPos)
{
	if (m_navMesh->CheckPolyIndex(enemyPos) == m_navMesh->CheckPolyIndex(playerPos))
	{
		return true;
	}

	return false;
}