#pragma once
#include"Actor3D.h"
#include"Vector3.h"

class LoadPlayer;
class Effect;
class Inventory;

class FirePlace : public Actor3D
{
private:
	static constexpr Vector3 CanWarmthRange = Vector3(600, 300, 600);	//‰·‚Ş‚±‚Æ‚ª‚Å‚«‚é”ÍˆÍ
	static constexpr Vector3 WarmthRangeOffset = Vector3(0,150,-200 );	//‰·‚Ş‚±‚Æ‚ª‚Å‚«‚é”ÍˆÍ

	static constexpr Vector3 FirePlacePos = Vector3(2000, 0, 800);

	static constexpr float FireDuration = 10.0f;

	float m_fireDuration;	//‰Î‚Ì‘±ŠÔ

	int m_model;

	Effect* m_effect;

	LoadPlayer* m_player;
	Inventory* m_inventory;

	bool isdeth = false;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	FirePlace(LoadPlayer* player,Inventory* inventory);
};