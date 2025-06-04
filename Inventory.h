#pragma once
#include "Item.h"
#include "Food.h"
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
	static constexpr Vector2 FontSize = Vector2(20, 35);	// 数字1文字の幅・高さ
	static constexpr int FontMargin = 5;					// 数字と数字の間の余白

	static constexpr int SquareSize = 100;

	int m_maxHaveItem;

	int m_haveFoodCount;	//アイテムを持ってる数
	int m_haveWoodCount;	//木を持っている数

	int m_takeItem;			//今何のアイテムを持っているか
	int m_dropItemNum;			//捨てたアイテムの番号

	bool m_canGetItem;			//アイテムを拾えるか
	bool m_gettingItem;			//アイテムを拾ったか
	bool m_dropItem;			//アイテムを落としたか
	bool m_dropItemCompletion;

	int m_itemNum;		//アイテムの番号格納用

	int m_seInventory;	//サウンド

	int m_fontTextureId;	// 数字フォント
	Transform m_haveWeightTransform;	// 姿勢

	//アイテム格納用
	std::vector<Food> m_foodList;
	Sprite m_inventoryUi;
	Sprite m_takeItemUi;
	Sprite m_woodIcon;
	Transform m_inventoryTransform;	// 姿勢
	Transform m_takeItemTransform;	// 姿勢
	Transform m_slashTransform;	// 姿勢

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

	//アイテムを拾ったときのアイコンの生成、重さの追加
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

	std::vector<Food*> GetItemAddlessList()
	{
		std::vector<Food*> addList;
		for (Food food : m_foodList)
		{
			Food* i = &food;
			addList.push_back(i);
		}

		return addList;
	}

	int GetTakeItem()
	{
		return m_takeItem;
	}

	int GetMaxHaveItem()
	{
		return m_maxHaveItem;
	}

	int GetHaveFoodCount()
	{
		return m_haveFoodCount;
	}

	void AddFoodCount()
	{
		m_haveFoodCount++;
	}

	void TakeCutWood(int woodValue)
	{
		m_haveWoodCount += woodValue;
	}

	int GetHaveWoodCount()
	{
		return m_haveWoodCount;
	}

	void LostHaveWood(int lostValue)
	{
		m_haveWoodCount -= lostValue;
	}
};