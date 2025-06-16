#include "TreeFactory.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "Inventory.h"
#include "Input.h"
#include "Seedling.h"

TreeFactory::TreeFactory(Ax* ax, LoadPlayer* player, Inventory* inventory) :
	m_ax(ax),
	m_player(player),
	m_inventory(inventory),
	m_cutTreeNum(0),
	m_tree(nullptr),
	m_seedling(nullptr),
	m_finishedGrowing(false),
	m_canPlantSeedling(false)
{
	m_tree = new Tree(m_ax, m_player, m_inventory, Vector3(-3000, 0, -500));

	AddChild(m_tree);

	AddTreeList(m_tree);
}

void TreeFactory::Update()
{
	//�A�����ʒu�܂ŗ�����A�����悤��
	if (m_player->GetPosition().x <= CanPlantRangeXPos)
	{
		m_canPlantSeedling = true;
		CanPlantSeedling();
	}
	else
	{
		m_canPlantSeedling = false;
	}


	if (!m_treeList.empty())
	{
		SearchCutTree();
	}

	if (m_player->GetCutTree())
	{
		//�؂𔰂�I�������
		FallDownTree();
	}

	//�c�؂�A�����ʒu�ɗ�����
	if (m_canPlantSeedling)
	{
		PlantSeedling();
	}

	if (!m_seedlingList.empty() && !m_finishedGrowing)
	{
		//�c�؂��炿�I�������
		FinishedGrowing();
	}
}

void TreeFactory::SearchCutTree()
{
	for (int i = 0; i <= m_treeList.size() - 1; i++)
	{
		//�v���C���[��X���W�̒��ɂ��邩
		if (m_treeList[i]->GetPosition().x + CanCutRangeHalf >= m_player->GetPosition().x &&
			m_treeList[i]->GetPosition().x - CanCutRangeHalf <= m_player->GetPosition().x)
		{
			//�v���C���[��Y���W�̒��ɂ��邩
			if (m_treeList[i]->GetPosition().z + CanCutRangeHalf >= m_player->GetPosition().z &&
				m_treeList[i]->GetPosition().z - CanCutRangeHalf <= m_player->GetPosition().z)
			{
				m_cutTreeNum = i;
				//�؂̋߂��ł͕c�؂𖄂߂��Ȃ��悤��
				m_canPlantSeedling = false;
			}
		}
	}
}

void TreeFactory::PlantSeedling()
{
	//F����������c�؂�A����
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_F))
	{
		m_seedling = new Seedling(m_ax, m_player, m_inventory, this, m_player->GetPosition());

		AddChild(m_seedling);

		m_seedlingList.push_back(m_seedling);
	}
}
 
void TreeFactory::FinishedGrowing()
{
	for (int i = 0; i <= m_seedlingList.size() - 1; i++)
	{
		if (m_seedlingList[i]->GetIsGrow())
		{
			m_tree = new Tree(m_ax,
				m_player,
				m_inventory,
				m_seedlingList[i]->GetPosition());

			//�؂𐶐�
			AddChild(m_tree);

			//�؃��X�g�ɒǉ�
			AddTreeList(m_tree);

			//�c�؂��폜
			m_seedlingList[i]->DestroyMe();
			//�c�؃��X�g����폜
			m_seedlingList.erase(m_seedlingList.begin() + i);

			m_finishedGrowing = true;
		}

		if (m_finishedGrowing)
		{
			m_finishedGrowing = false;

			break;
		}
	}
}

void TreeFactory::FallDownTree()
{
	for (int i = 0; i <= m_treeList.size() - 1; i++)
	{
		//�؂𔰂�I������
		if (m_treeList[i]->GetIsDeth())
		{
			//�؂��폜
			m_treeList[m_cutTreeNum]->DestroyMe();
			//�؃��X�g����폜
			m_treeList.erase(m_treeList.begin() + m_cutTreeNum);

			m_player->FellDownTree();

			m_cutTreeNum = 0;

			m_treeList[i]->ResetIsDeth();
		}
	}
}

void TreeFactory::CanPlantSeedling()
{
	if (!m_treeList.empty())
	{
		for (int i = 0; i <= m_treeList.size() - 1; i++)
		{
			//�v���C���[��X���W�̒��ɂ��邩
			if (m_treeList[i]->GetPosition().x + CanCutRangeHalf >= m_player->GetPosition().x &&
				m_treeList[i]->GetPosition().x - CanCutRangeHalf <= m_player->GetPosition().x)
			{
				//�v���C���[��Y���W�̒��ɂ��邩
				if (m_treeList[i]->GetPosition().z + CanCutRangeHalf >= m_player->GetPosition().z &&
					m_treeList[i]->GetPosition().z - CanCutRangeHalf <= m_player->GetPosition().z)
				{
					//�؂̋߂��ł͕c�؂𖄂߂��Ȃ��悤��
					m_canPlantSeedling = false;
				}
			}
		}
	}

	if (!m_seedlingList.empty())
	{
		for (int i = 0; i <= m_seedlingList.size() - 1; i++)
		{
			//�v���C���[��X���W�̒��ɂ��邩
			if (m_seedlingList[i]->GetPosition().x + CanCutRangeHalf >= m_player->GetPosition().x &&
				m_seedlingList[i]->GetPosition().x - CanCutRangeHalf <= m_player->GetPosition().x)
			{
				//�v���C���[��Y���W�̒��ɂ��邩
				if (m_seedlingList[i]->GetPosition().z + CanCutRangeHalf >= m_player->GetPosition().z &&
					m_seedlingList[i]->GetPosition().z - CanCutRangeHalf <= m_player->GetPosition().z)
				{
					//�c�؂̋߂��ł͕c�؂𖄂߂��Ȃ��悤��
					m_canPlantSeedling = false;
				}
			}
		}
	}
}