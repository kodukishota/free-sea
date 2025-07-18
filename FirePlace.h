#pragma once
#include"Actor3D.h"
#include"Vector3.h"

class LoadPlayer;
class Effect;
class Inventory;

class FirePlace : public Actor3D
{
private:
	static constexpr Vector3 WarmthRangeView = Vector3(2000, 300, 2000);	//温むことができる範囲
	static constexpr float WarmthRange = 2000;	//温むことができる範囲

	static constexpr Vector3 FirePlacePos = Vector3(0, 0, 0);

	static constexpr float FireDuration = 45.0f;

	float m_fireDuration;	//火の持続時間

	int m_model;

	bool m_isFire;		//火がついているか

	Effect* m_effect;

	LoadPlayer* m_player;
	Inventory* m_inventory;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	FirePlace(LoadPlayer* player,Inventory* inventory);
};