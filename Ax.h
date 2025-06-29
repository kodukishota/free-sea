#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"Sprite.h"

class LoadPlayer;
class SkillCheck;
class Inventory;
class AxIcon;

class Ax : public Actor3D
{
private:
	//�O�b�h�̈ʒu
	static constexpr Vector3 GodSetPos = Vector3(50,50,-30);
	static constexpr int AxKind = 3;				//���̎�ސ�

	static constexpr float FirstDurabilityValue = 100;	//�ϋv��
	static constexpr int AttackDamage = 5;				//�U����
	static constexpr int ConsumptionDurability[AxKind] = { 5, 4, 3};	//���Ցϋv�l
	static constexpr float CutTreeValue[AxKind] = { 1.0f, 1.3f, 1.5f};	//���̖؂̎���{��

	Vector2 m_drawPos;

	int m_axId;		//���g���ǂ̎�ނ̕��Ȃ̂������ʂ���悤
	int m_haveCount;

	int m_seCut;

	float m_durabilityValue;		//�ϋv�l
	int m_attackDamage;				//�U����
	int m_consumptionDurability;	//���Ցϋv�l

	bool m_isCutTreeFlag;	//�؂𔰂�����

	float m_cutTreeValue; //�������؂̔{��

	LoadPlayer* m_player;
	SkillCheck* m_skillCheck;
	AxIcon* m_axIcon;
	Inventory* m_inventory;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Ax( LoadPlayer* player, SkillCheck* skillCheck,int haveCount,int axId, Inventory* inventory);

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

	void MyDestroy()
	{
		Destroy();
	}
};