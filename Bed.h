#pragma once
#include "Actor3D.h"
#include "Vector3.h"

class LoadPlayer;
class WorldTime;

class Bed : public Actor3D
{
private:
	static constexpr Vector3 BedPosition = Vector3(-500, 50, -400);
	static constexpr Vector3 CanSleepRnage = Vector3(500, 500, 500);	//ベットにインタラクトできる範囲

	bool m_canSleep;	//寝れることができるか

	int m_model;

	LoadPlayer* m_player;
	WorldTime* m_worldTime;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Bed(LoadPlayer* player,WorldTime* worldTime);
};