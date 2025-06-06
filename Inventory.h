#pragma once
#include "Item.h"
#include "Food.h"
#include "Node.h"
#include "Sprite.h"
#include "Transform.h"
#include <list>
#include <vector>

class LoadFoodData;
class LoadPlayer;
class EatButton;
class Food;

class Inventory : public Node
{
private:
	static constexpr Vector2 TakeItemUiPos = Vector2(60,890);
	static constexpr Vector2 AxInventoryUiPos = Vector2(60, 890);
	static constexpr Vector2 AxMenuInventoryUiPos = Vector2(150, 300);
	static constexpr Vector2 FoodInventoryUiPos = Vector2(150, 800);
	static constexpr Vector2 WoodIconPos = Vector2(370, 890);
	static constexpr Vector2 WoodMenuIconPos = Vector2(160, 400);
	static constexpr Vector2 FontSize = Vector2(20, 35);	// 数字1文字の幅・高さ
	static constexpr int FontMargin = 5;					// 数字と数字の間の余白

	static constexpr int MaxHaveItem = 10;

	static constexpr int MaxHaveAx = 3;
	static constexpr int MaxhaveFood = 10;

	static constexpr int SquareSize = 100;

	int m_maxHaveItem;

	int m_haveFoodCount;	//アイテムを持ってる数
	int m_haveWoodCount;	//木を持っている数

	int m_takeFood;			//今何のアイテムを持っているか
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
	Sprite m_axInventoryUi;
	Sprite m_foodInventoryUi;
	Sprite m_takeItemUi;
	Sprite m_woodIcon;
	Transform m_axInventoryPos;	// 姿勢
	Transform m_foodInventoryPos;	// 姿勢
	Transform m_takeItemTransform;	// 姿勢
	Transform m_haveWoodTransform;	// 姿勢

	LoadFoodData* m_loadFoodData;
	LoadPlayer* m_player;
	EatButton* m_eatButton;
	Food* m_food[MaxHaveItem];

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Inventory(LoadPlayer* player,LoadFoodData* loadFoodData);

	bool CanGetItem()
	{
		return m_canGetItem;
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

	int GetTakeFood()
	{
		return m_takeFood;
	}

	int GetHaveFoodCount()
	{
		return m_haveFoodCount;
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

	void CreateFoodIcon(int foodId);

	void EatFood();
};