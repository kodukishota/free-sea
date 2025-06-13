#pragma once
#include "Actor3D.h"

class Ax;
class LoadPlayer;
class Inventory;

class Seedling : public Actor3D
{
private:
	static constexpr float GrowthTime = 10;

	int m_model;

	float m_growthTime;	//�c�؂��؂ɐ������鎞��

	Ax* m_ax;
	LoadPlayer* m_player;
	Inventory* m_inventory;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Seedling(Ax* ax, LoadPlayer* player, Inventory* inventory, Vector3 position);
};