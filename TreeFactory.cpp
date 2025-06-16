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
	//植えれる位置まで来たら植えれるように
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
		//木を伐り終わったら
		FallDownTree();
	}

	//苗木を植えれる位置に来たら
	if (m_canPlantSeedling)
	{
		PlantSeedling();
	}

	if (!m_seedlingList.empty() && !m_finishedGrowing)
	{
		//苗木が育ち終わったら
		FinishedGrowing();
	}
}

void TreeFactory::SearchCutTree()
{
	for (int i = 0; i <= m_treeList.size() - 1; i++)
	{
		//プレイヤーがX座標の中にいるか
		if (m_treeList[i]->GetPosition().x + CanCutRangeHalf >= m_player->GetPosition().x &&
			m_treeList[i]->GetPosition().x - CanCutRangeHalf <= m_player->GetPosition().x)
		{
			//プレイヤーがY座標の中にいるか
			if (m_treeList[i]->GetPosition().z + CanCutRangeHalf >= m_player->GetPosition().z &&
				m_treeList[i]->GetPosition().z - CanCutRangeHalf <= m_player->GetPosition().z)
			{
				m_cutTreeNum = i;
				//木の近くでは苗木を埋められないように
				m_canPlantSeedling = false;
			}
		}
	}
}

void TreeFactory::PlantSeedling()
{
	//Fを押したら苗木を植える
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

			//木を生成
			AddChild(m_tree);

			//木リストに追加
			AddTreeList(m_tree);

			//苗木を削除
			m_seedlingList[i]->DestroyMe();
			//苗木リストから削除
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
		//木を伐り終えたら
		if (m_treeList[i]->GetIsDeth())
		{
			//木を削除
			m_treeList[m_cutTreeNum]->DestroyMe();
			//木リストから削除
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
			//プレイヤーがX座標の中にいるか
			if (m_treeList[i]->GetPosition().x + CanCutRangeHalf >= m_player->GetPosition().x &&
				m_treeList[i]->GetPosition().x - CanCutRangeHalf <= m_player->GetPosition().x)
			{
				//プレイヤーがY座標の中にいるか
				if (m_treeList[i]->GetPosition().z + CanCutRangeHalf >= m_player->GetPosition().z &&
					m_treeList[i]->GetPosition().z - CanCutRangeHalf <= m_player->GetPosition().z)
				{
					//木の近くでは苗木を埋められないように
					m_canPlantSeedling = false;
				}
			}
		}
	}

	if (!m_seedlingList.empty())
	{
		for (int i = 0; i <= m_seedlingList.size() - 1; i++)
		{
			//プレイヤーがX座標の中にいるか
			if (m_seedlingList[i]->GetPosition().x + CanCutRangeHalf >= m_player->GetPosition().x &&
				m_seedlingList[i]->GetPosition().x - CanCutRangeHalf <= m_player->GetPosition().x)
			{
				//プレイヤーがY座標の中にいるか
				if (m_seedlingList[i]->GetPosition().z + CanCutRangeHalf >= m_player->GetPosition().z &&
					m_seedlingList[i]->GetPosition().z - CanCutRangeHalf <= m_player->GetPosition().z)
				{
					//苗木の近くでは苗木を埋められないように
					m_canPlantSeedling = false;
				}
			}
		}
	}
}