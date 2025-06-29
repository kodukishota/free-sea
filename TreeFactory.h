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

	static constexpr float CanCutRange = 600;		//�c�؂�A����Ƃ��̐A�����Ԋu
	static constexpr float CanPlantRangeXPos = -2200;	//�؂𐶂₹����W�̒[

	int m_cutTreeNum;	//�����Ă���؂����ʗp�ԍ�

	bool m_canPlantSeedling;	//�c�؂�A���邱�Ƃ��ł��邩
	bool m_finishedGrowing;		//�������I�������

	bool m_finishCut;	//����I�������

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

	//�ǂ̖؂𔰂��Ă��邩�𔻒f
	void SearchCutTree();

	void AddTreeList(Tree* tree)
	{
		m_treeList.push_back(tree);
	}

	//�c�؂�A����
	void PlantSeedling();

	//�c�؂����������
	void FinishedGrowing();

	//�؂𔰂�I�������
	void FallDownTree();

	//�c�؂�A�����ʒu��
	void CanPlantSeedling();
};