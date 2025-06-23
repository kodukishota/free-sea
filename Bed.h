#pragma once
#include "Actor3D.h"
#include "Vector3.h"

class LoadPlayer;
class WorldTime;

class Bed : public Actor3D
{
private:
	static constexpr Vector3 BedPosition = Vector3(-1100, 50, -400);
	static constexpr Vector3 CanSleepRnage = Vector3(500, 500, 500);	//�x�b�g�ɃC���^���N�g�ł���͈�
	static constexpr Vector3 CanSleepRnageOffset = Vector3(100, 0, 0);	//�x�b�g�ɃC���^���N�g�ł���͈�

	bool m_canSleep;	//�Q��邱�Ƃ��ł��邩

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