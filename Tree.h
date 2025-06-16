#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"DxLib.h"

class Ax;
class LoadPlayer;
class Inventory;

class Tree : public Actor3D
{
private:
	static constexpr Vector3 CanCutRange = Vector3(300, 150, 300);	//–Ø‚ğ”°‚ê‚é”ÍˆÍ
	static constexpr int FristHelth = 50;	//‘Ï‹v—Í
	static constexpr int CutTreeTakeValue = 2;	//ˆê‰ñ”°‚Á‚½‚ç—‚¿‚é–Ø‚Ì”B

	int m_model;	//ƒ‚ƒfƒ‹

	int m_helth;	//‘Ì—Í

	Ax* m_ax;
	LoadPlayer* m_player;
	Inventory* m_inventory;

	bool m_isDeth;	//”°‚ç‚ê‚½‚©

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Tree(Ax* ax,LoadPlayer* player,Inventory* inventory,Vector3 position);

	Vector3 GetPosition()
	{
		return m_transform.position;
	}

	bool GetIsDeth()
	{
		return m_isDeth;
	}

	void ResetIsDeth()
	{
		m_isDeth = false;
	}

	void DestroyMe()
	{
		Destroy();
	}
};