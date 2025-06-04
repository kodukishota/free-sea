#pragma once
#include "Node.h" 
#include "Sprite.h"
#include "Transform.h"
#include "Vector2.h"

class TredeUi;

class Food : public Node
{
private:
	int m_foodNumber;	//食べ物を識別するための番号格納用
	const char* m_foodName;
	const char* m_flavorText;

	const char* m_iconName;

	bool m_canGetItem;

	Sprite m_iconUi;
	Transform m_iconPos;

	TredeUi* m_tredeUi;

	float m_playerToDistance;	//プレイヤーとの距離

protected:
	virtual void Load();
	virtual void Release();
	virtual void Update();
	virtual void Draw();

public:
	Food(int foodNum,TredeUi* m_tredeUi);
};
