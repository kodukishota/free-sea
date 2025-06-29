#pragma once
#include "Node.h"
#include "Tree.h"
#include "Vector2.h"
#include <vector>

class Ax;
class LoadPlayer;
class Inventory;
class Seedling;
class Tree;

class TreeFactory : public Node
{
private:
	static constexpr int FirstTreeValue = 10;
	static constexpr Vector3 FirstTreePos[FirstTreeValue] = 
	{ Vector3(-2200,0,-700),Vector3(-3000, 0, -500),Vector3(-3600, 0, -1000),Vector3(-4500, 0, -2000),Vector3(-6000, 0, -800),
	Vector3(-2900,0,-3000),Vector3(-3200,0,-4000),Vector3(-5200,0,-2600),Vector3(-4200,0,-3200),Vector3(-3200,0,-4700), };

	static constexpr Vector2 CutUiPos = Vector2(620, 700);

	static constexpr float CanCutRange = 600;		//•c–Ø‚ğA‚¦‚é‚Æ‚«‚ÌA‚¦‚ê‚éŠÔŠu
	static constexpr float CanPlantRangeXPos = -2200;	//–Ø‚ğ¶‚â‚¹‚éÀ•W‚Ì’[

	int m_cutTreeNum;	//”°‚Á‚Ä‚¢‚é–Ø‚ğ¯•Ê—p”Ô†

	bool m_canPlantSeedling;	//•c–Ø‚ğA‚¦‚é‚±‚Æ‚ª‚Å‚«‚é‚©
	bool m_finishedGrowing;		//¬’·‚ªI‚í‚Á‚½‚©

	bool m_finishCut;	//”°‚èI‚í‚Á‚½‚©

	int m_cutUi;

	std::vector<Tree*> m_treeList;
	std::vector<Seedling*> m_seedlingList;

	Ax* m_ax;
	LoadPlayer* m_player;
	Inventory* m_inventory;
	Tree* m_tree;
	Seedling* m_seedling;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

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