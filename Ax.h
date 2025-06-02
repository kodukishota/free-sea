#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"Sprite.h"

class LoadPlayer;
class Camera;
class SkillCheck;

class Ax : public Actor3D
{
private:
	//ƒOƒbƒh‚ÌˆÊ’u
	static constexpr Vector3 OffSet = Vector3(50,50,-30);
	static constexpr float FirstDurabilityValue = 100;	//‘Ï‹v—Í
	static constexpr int AttackDamage = 5;				//UŒ‚—Í
	static constexpr int ConsumptionDurability = 5;	//Á–Õ‘Ï‹v’l

	int m_model;

	float m_durabilityValue;		//‘Ï‹v’l
	int m_attackDamage;				//UŒ‚—Í
	int m_consumptionDurability;	//Á–Õ‘Ï‹v’l

	bool m_isCutTreeFlag;	//–Ø‚ğ”°‚Á‚½‚©

	float m_cutTreeValue; //”°‚Á‚½–Ø‚Ì”{—¦

	LoadPlayer* m_player;
	Camera* m_camera;
	SkillCheck* m_skillCheck;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Ax( LoadPlayer* player, Camera* camera, SkillCheck* skillCheck);

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
};