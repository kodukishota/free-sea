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
	//ƒOƒbƒh‚ÌˆÊ’u
	static constexpr Vector3 GodSetPos = Vector3(50,50,-30);
	static constexpr int AxKind = 3;				//•€‚Ìí—Ş”

	static constexpr float FirstDurabilityValue = 100;	//‘Ï‹v—Í
	static constexpr int AttackDamage = 5;				//UŒ‚—Í
	static constexpr int ConsumptionDurability[AxKind] = { 5, 4, 3};	//Á–Õ‘Ï‹v’l
	static constexpr float CutTreeValue[AxKind] = { 1.0f, 1.3f, 1.5f};	//Œ³‚Ì–Ø‚Ìæ‚ê‚é”{—¦

	Vector2 m_drawPos;

	int m_axId;		//©g‚ª‚Ç‚Ìí—Ş‚Ì•€‚È‚Ì‚©‚ğ¯•Ê‚·‚é‚æ‚¤
	int m_haveCount;

	int m_seCut;

	float m_durabilityValue;		//‘Ï‹v’l
	int m_attackDamage;				//UŒ‚—Í
	int m_consumptionDurability;	//Á–Õ‘Ï‹v’l

	bool m_isCutTreeFlag;	//–Ø‚ğ”°‚Á‚½‚©

	float m_cutTreeValue; //”°‚Á‚½–Ø‚Ì”{—¦

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

	//–Ø‚ğ”°‚é
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