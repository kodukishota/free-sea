#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"Sprite.h"

class LoadPlayer;
class Camera;

class Ax : public Actor3D
{
private:
	static constexpr Vector2 SkillCheckUiPos = Vector2(720, 600);
	static constexpr Vector3 OffSet = Vector3(50,50,-30);
	static constexpr int FristDurabilityValue = 100;	//ëœãvóÕ
	static constexpr int AttackDamage = 10;				//çUåÇóÕ

	int m_model;

	int m_durabilityValue;
	int m_attackDamage;

	bool m_isCutTree;

	Sprite m_skillCheckUi;
	Sprite m_skillCheckHandleUi;
	Transform m_skillCheckUiPos;
	Transform m_skillCheckHandleUiPos;

	LoadPlayer* m_player;
	Camera* m_camera;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Ax( LoadPlayer* player, Camera* camera);

	void CutTree();

	int GetCutDamage()
	{
		return m_attackDamage;
	}

	bool GetIsCutTree()
	{
		return m_isCutTree;
	}
};