#pragma once
#include "Actor3D.h"
#include "Vector3.h"

class LoadPlayer;

class Bed : public Actor3D
{
private:
	static constexpr Vector3 BedPosition = Vector3(-500, 0, -400);
	static constexpr Vector3 CanSleepRnage = Vector3(400, 50, 300);	//�x�b�g�ɃC���^���N�g�ł���͈�

	bool m_canSleep;	//�Q��邱�Ƃ��ł��邩

	int m_model;

	LoadPlayer* m_player;

protected:
	virtual void Update() override;

public:
	Bed(LoadPlayer* player);
};