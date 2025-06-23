#pragma once
#include"Actor3D.h"
#include"Vector3.h"

class LoadPlayer;
class Inventory;

class Tree : public Actor3D
{
private:
	static constexpr Vector3 CanCutRange = Vector3(300, 150, 300);	//�؂𔰂��͈�
	static constexpr int FristHelth = 50;	//�ϋv��
	static constexpr int CutTreeTakeValue = 2;	//��񔰂����痎����؂̐��B

	int m_model;	//���f��

	int m_helth;	//�̗�

	LoadPlayer* m_player;
	Inventory* m_inventory;

	bool m_isDeth;	//����ꂽ��

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