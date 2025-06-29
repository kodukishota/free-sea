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
class Ax;
class SkillCheck;

class Inventory : public Node
{
private:
	//現在持っている斧を強調表示するUIの初期位置
	static constexpr Vector2 TakeItemUiPos = Vector2(60,890);		
	static constexpr Vector2 AxInventoryUiPos = Vector2(60, 890);		//斧の枠の位置
	static constexpr Vector2 AxMenuInventoryUiPos = Vector2(150, 300);	//斧の枠の位置メニュー時
	static constexpr Vector2 FoodInventoryUiPos = Vector2(150, 800);	//食べ物欄の枠の位置
	static constexpr Vector2 WoodIconPos = Vector2(320, 850);
	static constexpr Vector2 MenuWoodIconPos = Vector2(125, 370);
	static constexpr Vector2 SeedlingIconPos = Vector2(500, 850);
	static constexpr Vector2 MenuSeedlingIconPos = Vector2(125, 450);
	static constexpr Vector2 WoodMenuIconPos = Vector2(160, 400);
	static constexpr Vector2 FontSize = Vector2(20, 35);	// 数字1文字の幅・高さ
	static constexpr int FontMargin = 5;					// 数字と数字の間の余白

	static constexpr int MaxHaveItem = 10;

	static constexpr int MaxHaveAx = 3;
	static constexpr int MaxhaveFood = 10;

	static constexpr int SquareSize = 100;

	int m_maxHaveItem;

	int m_haveFoodCount;	//たべものを持ってる数
	int m_haveWoodCount;	//木を持っている数
	int m_haveSeedlingCount;	//苗木を持っている数
	int m_haveAxCount;		//斧を持っている数
	
	int m_takeFood;	//今何のアイテムを持っているか
	int m_takeAx;	//今何番目の斧を持っているか

	bool m_canGetItem;			//アイテムを拾えるか
	bool m_gettingItem;			//アイテムを拾ったか
	bool m_dropItemCompletion;

	bool m_isCutTree;

	bool m_selectFood;		//アイテムを選択しているか
	int m_eatFoodPosNum;	//食べた食べ物の描画されている順番の番号
	bool m_eatFoodFlag;		//食べ物を食べたか

	int m_shiftIconCount;

	int m_itemNum;		//アイテムの番号格納用

	bool m_breakAx;

	int m_seInventory;	//サウンド
	int m_seEat;

	int m_fontTextureId;	// 数字フォント
	Transform m_haveWeightTransform;	// 姿勢

	//アイテム格納用
	std::vector<Food*> m_foodList;
	std::vector<Ax*> m_axList;

	Sprite m_axInventoryUi;
	Sprite m_foodInventoryUi;
	Sprite m_takeItemUi;
	Transform m_axInventoryPos;		// 姿勢
	Transform m_foodInventoryPos;	// 姿勢
	Transform m_takeItemTransform;	// 姿勢

	int m_woodIcon;
	int m_seedlingIcon;

	Vector2 m_woodIconPos;
	Vector2 m_seedlingIconPos;

	LoadFoodData* m_loadFoodData;
	LoadPlayer* m_player;
	EatButton* m_eatButton;
	Food* m_food;
	Ax* m_ax;
	SkillCheck* m_skillCheck;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Inventory(LoadPlayer* player,LoadFoodData* loadFoodData,SkillCheck* skillCheck);

	bool CanGetItem()
	{
		return m_canGetItem;
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

	bool GetEatFoodFlag()
	{
		return m_eatFoodFlag;
	}

	int GetEatFoodPosNum()
	{
		return m_eatFoodPosNum;
	}

	void AddShiftIconCount()
	{
		m_shiftIconCount++;
	}
 
	std::vector<Ax*> GetAxList()
	{
		return m_axList;
	}

	int GetTakeAx()
	{
		return m_takeAx;
	}

	int GetHaveSeedlingCount()
	{
		return m_haveSeedlingCount;
	}

	//苗木を植えたときに苗木の所持数を減らす
	void UseSeedling()
	{
		m_haveSeedlingCount--;
	}

	//苗木を購入したとき
	void BuySeedling()
	{
		m_haveSeedlingCount++;
	}

	bool GetBreakAx()
	{
		return m_breakAx;
	}

	bool GetIsCutTree()
	{
		return m_isCutTree;
	}
 
	//買った食べ物をメニューで表示させる
	void BuyFood(int foodId);

	//斧を買った時のアイコンを表示したり
	void BuyAx(int axId);

	//選択した食べ物を食べる
	void EatFood();

	//マウスホイールで斧を選択する
	void SelectAx();

	void BreakAx();
};