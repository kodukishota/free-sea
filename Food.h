#pragma once
#include "Node.h" 
#include "Sprite.h"
#include "Transform.h"
#include "Vector2.h"

class LoadFoodData;
class LoadPlayer;
class EatButton;
class Inventory;

struct FoodData
{
	char m_foodName[256];
	char m_iconName[256];
	char m_flavorText[256];
	int m_recoveryHungry;
	int m_warmthValue;
};

class Food : public Node
{
private:
	static constexpr Vector2 IconPos = Vector2(150, 800);
	static constexpr Vector2 IconSize = Vector2(100, 100);

	static constexpr Vector2 InventoryPos = Vector2(550,800);
	static constexpr Vector2 InventorySize = Vector2(1000, 100);

	int m_foodNumber;	//食べ物を識別するための番号格納用
	const char* m_foodName;
	const char* m_flavorText;

	int m_recoveryHungry;	//空腹回復量

	int m_drawPosNum;	//自身がインベントリの何番目に描画されるか

	bool m_isSelect;	//今選択されているか

	int m_mouseX;
	int m_mouseY;

	Sprite m_iconUi;
	Transform m_iconPos;

	LoadPlayer* m_player;
	EatButton* m_eatButton;
	Inventory* m_inventory;

	FoodData m_foodData;

protected:
	virtual void Load();
	virtual void Release();
	virtual void Update();
	virtual void Draw();

public:
	Food(int foodNum,
		LoadPlayer* player = nullptr,
		FoodData* foodData = nullptr,
		int drawPosNum = 0,
		EatButton* eatButton = nullptr,
		Inventory* inventory = nullptr
		);

	void SelectEatFood();

	bool GetIsSelect()
	{
		return m_isSelect;
	}

	int GetRecoveryHungry()
	{
		return m_recoveryHungry;
	}

	void DestroyFood()
	{
		Destroy();
	}

	int GetDrawPosNum()
	{
		return m_drawPosNum;
	}

	void ShiftDrawPos()
	{
		m_drawPosNum--;
		m_iconPos.position = IconPos;
		m_iconPos.position.x = m_iconPos.position.x + IconSize.x * m_drawPosNum;
	}

	Vector2 GetDrawPos()
	{
		return m_iconPos.position;
	}

	const char* GetFoodName()
	{
		return m_foodName;
	}

	const char* GetFlavorText()
	{
		return m_flavorText;
	}
};
