#pragma once
#include "Actor3D.h"

class Ax;
class LoadPlayer;
class Inventory;
class TreeFactory;
class Tree;

class Seedling : public Actor3D
{
private:
	static constexpr float GrowthTime = 2;	 //•c–Ø‚ª–Ø‚É¬’·‚·‚éŠÔ

	int m_model;

	float m_growthTime;	//•c–Ø‚ª–Ø‚É¬’·‚·‚éŠÔ

	Ax* m_ax;
	LoadPlayer* m_player;
	Inventory* m_inventory;
	TreeFactory* m_treeFactory;
	Tree* m_tree;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Seedling(Ax* ax,
		LoadPlayer* player,
		Inventory* inventory,
		TreeFactory* treeFactory,
		Vector3 position);

	bool GetIsGrow();

	Vector3 GetPosition()
	{
		return m_transform.position;
	}

	void DestroyMe()
	{
		Destroy();
	}
};