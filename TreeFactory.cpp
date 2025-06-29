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
	//A‚¦‚ê‚éˆÊ’u‚Ü‚Å—ˆ‚½‚çA‚¦‚ê‚é‚æ‚¤‚É
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
		//–Ø‚ğ”°‚èI‚í‚Á‚½‚ç
		FallDownTree();
	}

	//•c–Ø‚ğA‚¦‚ê‚éˆÊ’u‚É—ˆ‚½‚ç
	if (m_canPlantSeedling && m_inventory->GetHaveSeedlingCount() > 0)
	{
		PlantSeedling();
	}

	if (!m_seedlingList.empty() && !m_finishedGrowing)
	{
		//•c–Ø‚ªˆç‚¿I‚í‚Á‚½‚ç
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

//ƒvƒŒƒCƒ„[‚ª‚Ç‚±‚Ì–Ø‚ğ”°‚Á‚Ä‚¢‚é‚©
void TreeFactory::SearchCutTree()
{
	for (int i = 0; i <= m_treeList.size() - 1; i++)
	{
		//ƒvƒŒƒCƒ„[‚ªXÀ•W‚Ì’†‚É‚¢‚é‚©
		if (m_player->CanInteractObject(m_treeList[i]->GetPosition(), CanCutRange))
		{			
			m_cutTreeNum = i;
			//–Ø‚Ì‹ß‚­‚Å‚Í•c–Ø‚ğ–„‚ß‚ç‚ê‚È‚¢‚æ‚¤‚É
			m_canPlantSeedling = false;
		}
	}
}

void TreeFactory::PlantSeedling()
{
	//F‚ğ‰Ÿ‚µ‚½‚ç•c–Ø‚ğA‚¦‚é
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_F))
	{
		m_seedling = new Seedling(m_ax, m_player, m_inventory, this, m_player->GetPosition());

		AddChild(m_seedling);
		//•c–ØƒŠƒXƒg‚É‚¢‚ê‚é
		m_seedlingList.push_back(m_seedling);

		//•c–Ø‚ÌŠ”‚ğŒ¸‚ç‚·
		m_inventory->UseSeedling();
	}
}
 
//•c–Ø‚ª¬’·‚µ‚«‚Á‚½ˆ—
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

			//–Ø‚ğ¶¬
			AddChild(m_tree);

			//–ØƒŠƒXƒg‚É’Ç‰Á
			AddTreeList(m_tree);

			//•c–Ø‚ğíœ
			m_seedlingList[i]->DestroyMe();
			//•c–ØƒŠƒXƒg‚©‚çíœ
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
		//–Ø‚ğ”°‚èI‚¦‚½‚ç
		if (m_treeList[i]->GetIsDeth())
		{
			m_player->FellDownTree();

			m_treeList[i]->ResetIsDeth();

			//–Ø‚ğíœ
			m_treeList[m_cutTreeNum]->DestroyMe();
			//–ØƒŠƒXƒg‚©‚çíœ
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
				//–Ø‚Ì‹ß‚­‚Å‚Í•c–Ø‚ğ–„‚ß‚ç‚ê‚È‚¢‚æ‚¤‚É
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
				//•c–Ø‚Ì‹ß‚­‚Å‚Í•c–Ø‚ğ–„‚ß‚ç‚ê‚È‚¢‚æ‚¤‚É
				m_canPlantSeedling = false;		
			}
		}
	}
}