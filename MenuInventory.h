#pragma once
#include "Item.h"
#include "Node.h"
#include "Sprite.h"
#include "Transform.h"
#include <vector>

class Chest;
class EnhanceType;

class MenuInventory : public Node
{
private:
	static constexpr int MaxHaveItem = 5;
	static constexpr Vector2 TakeItemUiPos = Vector2(250,870);
	static constexpr Vector2 InventoryUiPos = Vector2(250, 870);
	static constexpr Vector2 SlashUiPos = Vector2(105, 870);
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��

	static constexpr int SquareSize = 90;

	int m_maxHaveItem;

	int m_haveItemCount;	//�A�C�e���������Ă鐔
	int m_takeItem;			//�����Ԗڂ̃A�C�e���������Ă��邩

	int m_destroyTakeItem;	//�̂Ă��Ƃ��ǂ��̃A�C�e���������Ă�����
	bool m_gettingItem;		//�A�C�e�����`�F�X�g����C���x���g���������Ă�����

	bool m_isIventory;		//�C���x���g����G���Ă�Ƃ�

	int m_itemNum;		//�A�C�e���̔ԍ��i�[�p
	bool m_destroyItemIcon;		//�A�C�R����������
	int m_nowHaveWeight;

	int m_seInventory;	//�T�E���h

	std::vector<Item> m_itemList;
	std::vector<Item*> m_addItemList;

	Sprite m_menuInventoryUi;
	Sprite m_takeItemUi;
	Sprite m_slashUi;
	Transform m_transform;
	Transform m_takeItemTransform;	// �p��
	Transform m_slashTransform;	// �p��

	Chest* m_chest;
	EnhanceType* m_enhanceType;

	int m_fontTextureId;	// �����t�H���g
	Transform m_haveWeightTransform;	// �p��

	bool haveitem = m_itemList.empty();

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	MenuInventory(Chest* chest,EnhanceType* enhancetype);

	bool DestoryItemIcon() 
	{
		return m_destroyItemIcon;
	}

	int DestroyTakeItem()
	{
		return m_destroyTakeItem;
	}

	bool GetTakeInventory()
	{
		return m_isIventory;
	}

	void SetIsInventory(bool nowTake)
	{
		m_isIventory = nowTake;
	}

	void GettingItem() 
	{
		m_gettingItem = true;
	}
	
	std::vector<Item> GetItemList()
	{
		return m_itemList;
	}

	void Change(Item item)
	{
		m_itemList.push_back(item);
	}

	void AddAdvanceItemList(Item* item)
	{
		m_addItemList.push_back(item);
	}

	void AddItemCount()
	{
		m_haveItemCount++;
	}

	//�A�C�e�����E�����Ƃ��̃A�C�R���̐����A�d���̒ǉ�
	void TakeItem(Item* item);

	void CheckCanAddItem();
};