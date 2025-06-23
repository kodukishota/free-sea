#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"Sprite.h"

class LoadPlayer;
class SkillCheck;
class AxIcon;

class Ax : public Actor3D
{
private:
	//�O�b�h�̈ʒu
	static constexpr Vector3 OffSet = Vector3(50,50,-30);
	static constexpr float FirstDurabilityValue = 100;	//�ϋv��
	static constexpr int AttackDamage = 5;				//�U����
	static constexpr int ConsumptionDurability = 5;	//���Ցϋv�l

	Vector2 m_drawPos;

	int m_model;
	int m_seCut;

	float m_durabilityValue;		//�ϋv�l
	int m_attackDamage;				//�U����
	int m_consumptionDurability;	//���Ցϋv�l

	bool m_isCutTreeFlag;	//�؂𔰂�����

	float m_cutTreeValue; //�������؂̔{��

	LoadPlayer* m_player;
	SkillCheck* m_skillCheck;
	AxIcon* m_axIcon;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Ax( LoadPlayer* player, SkillCheck* skillCheck,int haveCount);

	//�؂𔰂�
	void CutTree();

	int GetCutDamage()
	{
		return m_attackDamage;
	}

	bool GetIsCutTree()
	{
		return m_isCutTreeFlag;
	}

	void OffIsCutTree()
	{
		m_isCutTreeFlag = false;
	}

	float GetDurability()
	{
		return m_durabilityValue;
	}

	float GetMaxDurability()
	{
		return FirstDurabilityValue;
	}

	float GetCutTreeMagnification()
	{
		return m_cutTreeValue;
	}

	void SetDrawPos(Vector2 drawPos)
	{
		m_drawPos = drawPos;
	}

	Vector2 GetDrawPos()
	{
		return m_drawPos;
	}
};