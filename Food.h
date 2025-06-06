#pragma once
#include "Node.h" 
#include "Sprite.h"
#include "Transform.h"
#include "Vector2.h"

class LoadFoodData;
class LoadPlayer;
class EatButton;

struct FoodData
{
	char m_foodName[256];
	char m_iconName[256];
	char m_flavorText[256];
	int m_recoveryHungry;
};

class Food : public Node
{
private:
	static constexpr Vector2 IconPos = Vector2(150, 800);
	static constexpr Vector2 IconSize = Vector2(100, 100);

	static constexpr Vector2 InventoryPos = Vector2(550,800);
	static constexpr Vector2 InventorySize = Vector2(1000, 100);

	int m_foodNumber;	//êHÇ◊ï®ÇéØï Ç∑ÇÈÇΩÇﬂÇÃî‘çÜäiî[óp
	const char* m_foodName;
	const char* m_flavorText;

	int m_recoveryHungry;	//ãÛï†âÒïúó 

	bool m_canGetItem;

	bool m_isSelect;

	int m_mouseX;
	int m_mouseY;

	Sprite m_iconUi;
	Transform m_iconPos;

	LoadPlayer* m_player;
	EatButton* m_eatButton;

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
		EatButton* eatButton = nullptr
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
};
