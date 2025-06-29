#include "TreeFactory.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "Inventory.h"
#include "Input.h"
#include "Seedling.h"
#include "ImageLoader.h"

TreeFactory::TreeFactory(Ax* ax, LoadPlayer* player, Inventory* inventory) :
	m_ax(ax),
	m_player(player),
	m_inventory(inventory),
	m_cutTreeNum(0),
	m_tree(nullptr),
	m_seedling(nullptr),
	m_finishedGrowing(false),
	m_canPlantSeedling(false),
	m_cutUi(0)
{

	for (int i = 0; i <= FirstTreeValue - 1; i++)
	{
		m_tree = new Tree(m_player, m_inventory, FirstTreePos[i]);
	
		AddChild(m_tree);
	
		AddTreeList(m_tree);
	}
}

void TreeFactory::Load()
{
	m_cutUi = ImageLoader::GetInstance()->Load("cut_ui.png");
}

void TreeFactory::Release()
{
	ImageLoader::GetInstance()->Delete("cut_ui.png");
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
	if (m_canPlantSeedling && m_inventory->GetHaveSeedlingCount() > 0)
	{
		PlantSeedling();
	}

	if (!m_seedlingList.empty() && !m_finishedGrowing)
	{
		//�c�؂��炿�I�������
		FinishedGrowing();
	}
}

void TreeFactory::Draw()
{
	for (int i = 0; i <= m_treeList.size() - 1; i++)
	{
		if (m_player->CanInteractObject(m_treeList[i]->GetPosition(), CanCutRange) && 
			!m_player->GetCutTree())
		{
			DrawGraph(static_cast<int>(CutUiPos.x), static_cast<int>(CutUiPos.y), m_cutUi, true);
		}
	}
}

//�v���C���[���ǂ��̖؂𔰂��Ă��邩
void TreeFactory::SearchCutTree()
{
	for (int i = 0; i <= m_treeList.size() - 1; i++)
	{
		//�v���C���[��X���W�̒��ɂ��邩
		if (m_player->CanInteractObject(m_treeList[i]->GetPosition(), CanCutRange))
		{			
			m_cutTreeNum = i;
			//�؂̋߂��ł͕c�؂𖄂߂��Ȃ��悤��
			m_canPlantSeedling = false;
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
		//�c�؃��X�g�ɂ����
		m_seedlingList.push_back(m_seedling);

		//�c�؂̏����������炷
		m_inventory->UseSeedling();
	}
}
 
//�c�؂�����������������
void TreeFactory::FinishedGrowing()
{
	for (int i = 0; i <= m_seedlingList.size() - 1; i++)
	{
		if (m_seedlingList[i]->GetIsGrow())
		{
			m_tree = new Tree(
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
			m_player->FellDownTree();

			m_treeList[i]->ResetIsDeth();

			//�؂��폜
			m_treeList[m_cutTreeNum]->DestroyMe();
			//�؃��X�g����폜
			m_treeList.erase(m_treeList.begin() + m_cutTreeNum);

			m_cutTreeNum = 0;

			m_finishCut = true;
		}

		if (m_finishCut)
		{
			break;
			m_finishCut = false;
		}
	}
}

void TreeFactory::CanPlantSeedling()
{
	if (!m_treeList.empty())
	{
		for (int i = 0; i <= m_treeList.size() - 1; i++)
		{
			if (m_player->CanInteractObject(m_treeList[i]->GetPosition(), CanCutRange))
			{
				//�؂̋߂��ł͕c�؂𖄂߂��Ȃ��悤��
				m_canPlantSeedling = false;
			}
		}
	}

	if (!m_seedlingList.empty())
	{
		for (int i = 0; i <= m_seedlingList.size() - 1; i++)
		{
			if (m_player->CanInteractObject(m_seedlingList[i]->GetPosition(), CanCutRange))
			{
				//�c�؂̋߂��ł͕c�؂𖄂߂��Ȃ��悤��
				m_canPlantSeedling = false;		
			}
		}
	}
}