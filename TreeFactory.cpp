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
	if (m_canPlantSeedling && m_inventory->GetHaveSeedlingCount() > 0)
	{
		PlantSeedling();
	}

	if (!m_seedlingList.empty() && !m_finishedGrowing)
	{
		//苗木が育ち終わったら
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

//プレイヤーがどこの木を伐っているか
void TreeFactory::SearchCutTree()
{
	for (int i = 0; i <= m_treeList.size() - 1; i++)
	{
		//プレイヤーがX座標の中にいるか
		if (m_player->CanInteractObject(m_treeList[i]->GetPosition(), CanCutRange))
		{			
			m_cutTreeNum = i;
			//木の近くでは苗木を埋められないように
			m_canPlantSeedling = false;
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
		//苗木リストにいれる
		m_seedlingList.push_back(m_seedling);

		//苗木の所持数を減らす
		m_inventory->UseSeedling();
	}
}
 
//苗木が成長しきった処理
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
			m_player->FellDownTree();

			m_treeList[i]->ResetIsDeth();

			//木を削除
			m_treeList[m_cutTreeNum]->DestroyMe();
			//木リストから削除
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
				//木の近くでは苗木を埋められないように
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
				//苗木の近くでは苗木を埋められないように
				m_canPlantSeedling = false;		
			}
		}
	}
}