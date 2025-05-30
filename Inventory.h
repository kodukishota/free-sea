#pragma once
#include "Item.h"
#include "Node.h"
#include "Sprite.h"
#include "Transform.h"
#include <list>
#include <vector>

class Inventory : public Node
{
private:
	static constexpr Vector2 TakeItemUiPos = Vector2(60,890);
	static constexpr Vector2 InventoryUiPos = Vector2(60, 890);
	static constexpr Vector2 WoodIconPos = Vector2(200, 890);
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��

	static constexpr int SquareSize = 100;

	int m_maxHaveItem;

	int m_haveItemCount;	//�A�C�e���������Ă鐔
	int m_haveWoodCount;	//�؂������Ă��鐔

	int m_takeItem;			//�����̃A�C�e���������Ă��邩
	int m_dropItemNum;			//�̂Ă��A�C�e���̔ԍ�

	int m_nowHaveWeight;	//���ǂꂮ�炢�̏d�������Ă��邩

	bool m_canGetItem;			//�A�C�e�����E���邩
	bool m_gettingItem;			//�A�C�e�����E������
	bool m_dropItem;			//�A�C�e���𗎂Ƃ�����
	bool m_dropItemCompletion;

	int m_itemNum;		//�A�C�e���̔ԍ��i�[�p

	int m_seInventory;	//�T�E���h

	int m_fontTextureId;	// �����t�H���g
	Transform m_haveWeightTransform;	// �p��

	//�A�C�e���i�[�p
	std::vector<Item> m_itemList;   
	std::vector<Item*> m_addItemList;
	Sprite m_inventoryUi;
	Sprite m_takeItemUi;
	Sprite m_woodIcon;
	Transform m_inventoryTransform;	// �p��
	Transform m_takeItemTransform;	// �p��
	Transform m_slashTransform;	// �p��

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Inventory();

	bool CanGetItem()
	{
		return m_canGetItem;
	}

	//�A�C�e�����E�����Ƃ��̃A�C�R���̐����A�d���̒ǉ�
	void TakeItem(Item* item);

	bool GetItemNow()
	{
		return m_gettingItem;
	}

	void GettingItem()
	{
		m_gettingItem = true;
	}

	bool GetDropItem()
	{
		return m_dropItem;
	}

	int GetDropItemNum()
	{
		return m_dropItemNum;
	}

	void GetDropItemCompletion()
	{
		m_dropItemCompletion = true;
	}

	std::vector<Item> GetItemList()
	{
		return m_itemList;
	}

	std::vector<Item*> GetItemAddlessList()
	{
		std::vector<Item*> addList;
		for (Item item : m_itemList)
		{
			Item* i = &item;
			addList.push_back(i);
		}

		return addList;
	}

	int GetTakeItem()
	{
		return m_takeItem;
	}

	void EnhanceInventory()
	{
		m_maxHaveItem++;
	}

	int GetMaxHaveItem()
	{
		return m_maxHaveItem;
	}

	int GetHaveItemCount()
	{
		return m_haveItemCount;
	}

	int GetHaveWeight()
	{
		return m_nowHaveWeight;
	}

	void AddItemCount()
	{
		m_haveItemCount++;
	}

	void ItemClear()
	{
		m_itemList.clear();
	}

	void AddAdvanceItemList(Item* item)
	{
		m_addItemList.push_back(item);
	}

	void CheckCanAddItem();

	void TakeCutWood(int woodValue)
	{
		m_haveWoodCount += woodValue;
	}
};