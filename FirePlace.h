#pragma once
#include"Actor3D.h"
#include"Vector3.h"

class LoadPlayer;

class FirePlace : public Actor3D
{
private:
	static constexpr Vector3 CanWarmthRange = Vector3(600, 300, 600);	//‰·‚Þ‚±‚Æ‚ª‚Å‚«‚é”ÍˆÍ
	static constexpr Vector3 WarmthRangeOffset = Vector3(0,150,-200 );	//‰·‚Þ‚±‚Æ‚ª‚Å‚«‚é”ÍˆÍ

	static constexpr Vector3 FirePlacePos = Vector3(2000, 0, 800);

	int m_model;

	LoadPlayer* m_player;

	bool isdeth = false;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	FirePlace(LoadPlayer* player);
};