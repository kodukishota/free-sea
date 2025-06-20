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
	static constexpr float CanCutRange = 600;		//�c�؂�A����Ƃ��̐A�����Ԋu
	static constexpr float CanPlantRangeXPos = -2400;	//�؂𐶂₹����W�̒[


	int m_cutTreeNum;	//�����Ă���؂����ʗp�ԍ�

	bool m_canPlantSeedling;	//�c�؂�A���邱�Ƃ��ł��邩
	bool m_finishedGrowing;		//�������I�������

	bool m_finishCut;	//����I�������

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