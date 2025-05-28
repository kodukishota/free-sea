#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"DxLib.h"

class Ax;
class LoadPlayer;

class Tree : public Actor3D
{
private:
	static constexpr Vector3 CanCutRange = Vector3(300, 150, 300);	//–Ø‚ð”°‚ê‚é”ÍˆÍ

	static constexpr Vector3 OffSet = Vector3(1000, 0, 600);
	static constexpr int FristHelth = 100;	//‘Ï‹v—Í

	int m_model;

	int m_helth;

	Ax* m_ax;
	LoadPlayer* m_player;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Tree(Ax* ax,LoadPlayer* player);
};