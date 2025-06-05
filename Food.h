#pragma once
#include "Node.h" 
#include "Sprite.h"
#include "Transform.h"
#include "Vector2.h"

class LoadFoodData;
class LoadPlayer;

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
	static constexpr Vector2 IconPos = Vector2(200, 300);
	static constexpr Vector2 IconSize = Vector2(100, 100);

	int m_foodNumber;	//食べ物を識別するための番号格納用
	const char* m_foodName;
	const char* m_flavorText;

	int m_recoveryHungry;	//空腹回復量

	bool m_canGetItem;

	int MouseX;
	int MouseY;

	Sprite m_iconUi;
	Transform m_iconPos;

	LoadFoodData* m_loadFoodData;
	LoadPlayer* m_player;

	float m_playerToDistance;	//プレイヤーとの距離

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
		int drawPosNum = 0
		);
};
