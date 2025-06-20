#pragma once
#include "Node.h"
#include "Tree.h"
#include <vector>

class Ax;
class LoadPlayer;
class Inventory;
class Seedling;
class Tree;

class TreeFactory : public Node
{
private:
	static constexpr float CanCutRange = 600;		//•c–Ø‚ğA‚¦‚é‚Æ‚«‚ÌA‚¦‚ê‚éŠÔŠu
	static constexpr float CanPlantRangeXPos = -2400;	//–Ø‚ğ¶‚â‚¹‚éÀ•W‚Ì’[


	int m_cutTreeNum;	//”°‚Á‚Ä‚¢‚é–Ø‚ğ¯•Ê—p”Ô†

	bool m_canPlantSeedling;	//•c–Ø‚ğA‚¦‚é‚±‚Æ‚ª‚Å‚«‚é‚©
	bool m_finishedGrowing;		//¬’·‚ªI‚í‚Á‚½‚©

	bool m_finishCut;	//”°‚èI‚í‚Á‚½‚©

	std::vector<Tree*> m_treeList;
	std::vector<Seedling*> m_seedlingList;

	Ax* m_ax;
	LoadPlayer* m_player;
	Inventory* m_inventory;
	Tree* m_tree;
	Seedling* m_seedling;

protected:
	virtual void Update() override;

public:
	TreeFactory(Ax* ax, LoadPlayer* player, Inventory* inventory);

	//‚Ç‚Ì–Ø‚ğ”°‚Á‚Ä‚¢‚é‚©‚ğ”»’f
	void SearchCutTree();

	void AddTreeList(Tree* tree)
	{
		m_treeList.push_back(tree);
	}

	//•c–Ø‚ğA‚¦‚é
	void PlantSeedling();

	//•c–Ø‚ªˆç‚Á‚½‚ ‚Æ
	void FinishedGrowing();

	//–Ø‚ğ”°‚èI‚í‚Á‚½Œã
	void FallDownTree();

	//•c–Ø‚ğA‚¦‚ê‚éˆÊ’u‚©
	void CanPlantSeedling();
};