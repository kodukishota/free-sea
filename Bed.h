#pragma once
#include "Actor3D.h"
#include "Vector3.h"

class LoadPlayer;

class Bed : public Actor3D
{
private:
	static constexpr Vector3 BedPosition = Vector3(-500, 0, -400);
	static constexpr Vector3 CanSleepRnage = Vector3(400, 50, 300);	//ベットにインタラクトできる範囲

	bool m_canSleep;	//寝れることができるか

	int m_model;

	LoadPlayer* m_player;

protected:
	virtual void Update() override;

public:
	Bed(LoadPlayer* player);
};