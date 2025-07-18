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
	//グッドの位置
	static constexpr Vector3 GodSetPos = Vector3(50,50,-30);
	static constexpr int AxKind = 3;				//斧の種類数

	static constexpr float FirstDurabilityValue = 100;	//耐久力
	static constexpr int AttackDamage = 5;				//攻撃力
	static constexpr int ConsumptionDurability[AxKind] = { 5, 4, 3};	//消耗耐久値
	static constexpr float CutTreeValue[AxKind] = { 1.0f, 1.3f, 1.5f};	//元の木の取れる倍率

	Vector2 m_drawPos;

	int m_axId;		//自身がどの種類の斧なのかを識別するよう
	int m_haveCount;

	int m_seCut;

	float m_durabilityValue;		//耐久値
	int m_attackDamage;				//攻撃力
	int m_consumptionDurability;	//消耗耐久値

	bool m_isCutTreeFlag;	//木を伐ったか

	float m_cutTreeValue; //伐った木の倍率

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

	//木を伐る
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