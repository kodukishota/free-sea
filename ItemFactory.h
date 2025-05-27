#pragma once
#include"Node.h"
#include"Vector3.h"
#include"Item.h"
#include<vector>

class NavMesh;
class Inventory;
class LoadPlayer;

class ItemFactory : public Node
{
private:
	static constexpr int ItemNum = 40;
	static constexpr int ProbabilityEnhanceItem = 6;	// �����A�C�e�����I�΂�銄��
	static constexpr int ProbabilitySellItem = 4;		// ���p�p�A�C�e�����I�΂�銄��

	bool m_isFinish;		// �A�C�e�������ׂďW�ߏI������
	int m_getNum;		// �W�ߏI�����A�C�e����
	int m_itemType;	// �A�C�e���̎��(1:�����p, 2:���p�p)
	// �A�C�e���̃X�|�[���m����ς���p
	std::vector<Item::ItemNameList> m_forSellItemList;	// ���p�p�A�C�e��
	std::vector<Item::ItemNameList> m_forEnhanceItemList;	// �����p�A�C�e��

	ItemData m_itemData[static_cast<int>(Item::ItemNameList::Length)];

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	ItemFactory(
		Inventory* inventory,
		NavMesh* navMesh
	);

	// �N���A�t���O��Ԃ�
	bool IsFinish()
	{
		return m_isFinish;
	}

	void LoadItemData();

	ItemData* GetItemData(int itemNum)
	{
		return &m_itemData[itemNum];
	}
};