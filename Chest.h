#pragma once
#include "Item.h"
#include "Node.h"
#include "Sprite.h"
#include "Transform.h"
#include <vector>

class Chest : public Node
{
private:
	static constexpr int MaxHaveItem = 30;
	static constexpr Vector2 TakeItemUiPos = Vector2(235, 560);

	int m_haveItemCount;	//�A�C�e���������Ă鐔
	int m_takeItem;			//�����Ԗڂ̃A�C�e���������Ă��邩

	int m_destroyTakeItem;		//�̂Ă��Ƃ��ǂ��̃A�C�e���������Ă�����
	int m_destroyItemIconCount;	//���A�C�e���̃A�C�R������������

	bool m_canStorageItem;		//�A�C�e�������[�ł��邩
	bool m_storagingItem;		//�A�C�e�������[������

	bool m_isChest;		//�`�F�X�g��G���Ă���Ƃ�

	int m_itemNum;				//�A�C�e���̔ԍ��i�[�p
	bool m_destroyItemIcon;		//�A�C�R����������


	int m_seChest;	//�T�E���h

	std::vector<Item> m_itemList;
	std::vector<Item*> m_addItemList;
	std::vector<Item> m_lostItemList;

	Sprite m_chestUi;
	Sprite m_takeItemUi;
	Transform m_transform;
	Transform m_takeItemTransform;	// �p��

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Chest();

	bool DestroyItemIcon()
	{
		return m_destroyItemIcon;
	}

	void AddDestroyItemIconCount()
	{
		m_destroyItemIconCount++;
	}

	int DestroyTakeItem()
	{
		return m_destroyTakeItem;
	}

	bool GetTakeChest()
	{
		return	m_isChest;
	}

	bool GetCanStorageItem()
	{
		return m_canStorageItem;
	}

	void SetIsInventory(bool nowTake)
	{
		m_isChest = nowTake;
	}

	void SetItemList(int itemNum)
	{
		Item m_item = Item(itemNum);

		m_itemList.push_back(m_item);
	}

	void  StringingChest()
	{
		m_storagingItem = true;
	}

	std::vector<Item> GetItemList()
	{
		return m_itemList;
	}

	std::vector<Item> GetLostItemList()
	{
		return m_lostItemList;
	}

	int GetTakeItem() const
	{
		return m_takeItem;
	}

	void CreateIcon(Item* item);

	void AddItemCount()
	{
		m_haveItemCount++;
	}

	void AddAdvanceItemList(int itemNum, ItemData* itemData)
	{
		Item* item = new Item(itemNum, itemData);

		m_addItemList.push_back(item);
	}

	void CheckCanAddItem();

	void LostItem(int loatItemNum)
	{
		m_destroyTakeItem = loatItemNum;
		m_destroyItemIcon = true;

		//��ԍŌ�̃A�C�e����������G���[���N����������N����Ȃ��悤�ɂ��Ă�
		if (m_takeItem == m_itemList.size()-1)
		{
			m_takeItem = m_takeItem -1;
		}

		m_haveItemCount--;

		m_itemList.erase(m_itemList.begin() + loatItemNum);
	}
};