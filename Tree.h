#pragma once
#include"Actor3D.h"
#include"Vector3.h"

class LoadPlayer;
class Inventory;

class Tree : public Actor3D
{
private:
	static constexpr Vector3 CanCutRange = Vector3(300, 150, 300);	//木を伐れる範囲
	static constexpr int FristHelth = 50;	//耐久力
	static constexpr int CutTreeTakeValue = 2;	//一回伐ったら落ちる木の数。

	int m_model;	//モデル

	int m_helth;	//体力

	LoadPlayer* m_player;
	Inventory* m_inventory;

	bool m_isDeth;	//伐られたか

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Tree(LoadPlayer* player,Inventory* inventory,Vector3 position);

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