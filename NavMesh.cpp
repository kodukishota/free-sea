#include"NavMesh.h"
#include"CollisionStage.h"
#include"Math.h"
#include"Vector3.h"
#include <cstdlib>
#include <ctime>

NavMesh::NavMesh(CollisionStage* collisionStage) :
	m_collisionStage(collisionStage)
{
	srand(static_cast<unsigned int>(time(NULL)));
	// �ŏ��Ƀ|���S���̘A�������\�z���Ă���
	SetPolyLinkInfo();
}

// �w����W�̒����A����̃|���S���ԍ����擾�i�Ȃ��ꍇ��-1�j
int NavMesh::CheckPolyIndex(Vector3 pos)
{
	return m_collisionStage->CheckOnPolyIndex(pos, m_polyList);
}

// �|���S�����m�̘A�������쐬
void NavMesh::SetPolyLinkInfo()
{
	PolyLinkInfo* plInfo;
	PolyLinkInfo* plInfoSub;
	MV1_REF_POLYGON* refPoly;
	MV1_REF_POLYGON* refPolySub;

	int model = m_collisionStage->GetMeshModel();

	m_polyList = MV1GetReferenceMesh(model, -1, true);

	// �������̈���m��
	m_polyLink = new PolyLinkInfo[sizeof(PolyLinkInfo) * m_polyList.PolygonNum];

	plInfo = m_polyLink;
	refPoly = m_polyList.Polygons;
	// �S�|���S���̒��S���W���Z�o
	for (int i = 0; i < m_polyList.PolygonNum; i++, refPoly++, plInfo++)
	{
		plInfo->centerPos = VScale(
			VAdd(m_polyList.Vertexs[refPoly->VIndex[0]].Position,
				VAdd(m_polyList.Vertexs[refPoly->VIndex[1]].Position,
					m_polyList.Vertexs[refPoly->VIndex[2]].Position)),
			1.0f / 3.0f
		);
	}

	// �|���S�����m�̗אڏ����쐬
	plInfo = m_polyLink;
	refPoly = m_polyList.Polygons;

	for (int i = 0; i < m_polyList.PolygonNum; i++, plInfo++, refPoly++)
	{
		// �ŏ��ɗאڏ������Z�b�g����
		for (int j = 0; j < 3; j++)
		{
			plInfo->linkPolyIndex[j] = -1;
		}

		// �אڂ���|���S����T�����߂Ƀ|���S���̐������J��Ԃ�
		refPolySub = m_polyList.Polygons;
		plInfoSub = m_polyLink;

		// �אڏ���ǉ����悤�Ƃ��Ă���|���S���̒��_���W
		Vector3 vertexPos[3] = { Vector3(0, 0, 0) };
		for (int j = 0; j < 3; j++)
		{
			// �Ή������C���f�b�N�X�̗v�f�ɍ��W���R�s�[
			vertexPos[j] = m_polyList.Vertexs[refPoly->VIndex[j]].Position;
		}

		for (int j = 0; j < m_polyList.PolygonNum; j++, refPolySub++, plInfoSub++)
		{
			// �������g�𖳎�
			if (i == j) continue;

			Vector3 subVertexPos[3] = { Vector3(0, 0, 0) };

			// ���̎��ŗׂ荇���Ă��邩���ׂ�|���S���̒��_���W
			for (int k = 0; k < 3; k++)
			{
				subVertexPos[k] = m_polyList.Vertexs[refPolySub->VIndex[k]].Position;
			}

			// �@������|���S���̌������v�Z
			Vector3 v1 = subVertexPos[1] - subVertexPos[0];
			Vector3 v2 = subVertexPos[2] - subVertexPos[0];

			// �O��
			Vector3 outv = v1.CrossP(v2);
			outv = Math::Normalized(outv);

			// �p�x�����Ă���|���S���͏��Ƃ݂Ȃ��Ȃ�
			if (outv.y <= 0.5)
			{
				continue;
			}

			// �|���S�����_�ԍ�(0,1)�Ō`�������ӂƗאڂ��Ă�����אڏ��ɒǉ�
			if (
				plInfo->linkPolyIndex[0] == -1 &&
				((vertexPos[0] == subVertexPos[0] && vertexPos[1] == subVertexPos[2]) ||
					(vertexPos[0] == subVertexPos[1] && vertexPos[1] == subVertexPos[0]) ||
					(vertexPos[0] == subVertexPos[2] && vertexPos[1] == subVertexPos[1]))
				)
			{
				plInfo->linkPolyIndex[0] = j;
				plInfo->linkPolyDistance[0] = VSize(VSub(plInfoSub->centerPos, plInfo->centerPos));
			}
			// �|���S�����_�ԍ�(1,2)�Ō`�������ӂƗאڂ��Ă�����אڏ��ɒǉ�
			else if (
				plInfo->linkPolyIndex[1] == -1 &&
				((vertexPos[1] == subVertexPos[0] && vertexPos[2] == subVertexPos[2]) ||
					(vertexPos[1] == subVertexPos[1] && vertexPos[2] == subVertexPos[0]) ||
					(vertexPos[1] == subVertexPos[2] && vertexPos[2] == subVertexPos[1]))
				)
			{
				plInfo->linkPolyIndex[1] = j;
				plInfo->linkPolyDistance[1] = VSize(VSub(plInfoSub->centerPos, plInfo->centerPos));
			}
			// �|���S�����_�ԍ�(2,0)�Ō`�������ӂƗאڂ��Ă�����אڏ��ɒǉ�
			else if (
				plInfo->linkPolyIndex[2] == -1 &&
				((vertexPos[2] == subVertexPos[0] && vertexPos[0] == subVertexPos[2]) ||
					(vertexPos[2] == subVertexPos[1] && vertexPos[0] == subVertexPos[0]) ||
					(vertexPos[2] == subVertexPos[2] && vertexPos[0] == subVertexPos[1]))
				)
			{
				plInfo->linkPolyIndex[2] = j;
				plInfo->linkPolyDistance[2] = VSize(VSub(plInfoSub->centerPos, plInfo->centerPos));
			}
		}
	}
}

// �|���S�����m�̘A�����̍폜
void NavMesh::RemovePolyLinkInfo()
{
	delete[] m_polyLink;
}

// �|���S���̏����g���āA�|�W�V������Ԃ�
Vector3 NavMesh::GetPos(const int polygonNum)
{
	if (polygonNum == 0)
	{
		int index;
		Vector3 outv;

		// ���I�̏ꍇ�A�@������|���S���̊p�x���擾 => �����Ȃ��ꏊ�̎��͍Ē��I
		do
		{
			index = rand() % m_polyList.PolygonNum;

			Vector3 subVertexPos[3] = { Vector3(0, 0, 0) };

			// ���̎��ŗׂ荇���Ă��邩���ׂ�|���S���̒��_���W
			for (int k = 0; k < 3; k++)
			{
				subVertexPos[k] = m_polyList.Vertexs[m_polyList.Polygons[index].VIndex[k]].Position;
			}

			// �@������|���S���̌������v�Z
			Vector3 v1 = subVertexPos[1] - subVertexPos[0];
			Vector3 v2 = subVertexPos[2] - subVertexPos[0];

			// �O��
			outv = v1.CrossP(v2);
			outv = Math::Normalized(outv);
		} while (outv.y <= 0.5);
		
		return m_polyLink[index].centerPos;
	}
	else
	{
		return m_polyLink[polygonNum].centerPos;
	}
}