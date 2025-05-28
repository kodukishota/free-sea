#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"Sprite.h"

class LoadPlayer;
class Camera;

class Ax : public Actor3D
{
private:
	static constexpr int GoodHandleUiPosIndex = 9;
	//グッドの位置
	static constexpr int GoodHandleUiPosX[GoodHandleUiPosIndex] = {420,495,570,645,720,795,870,945,1020 };
	static constexpr Vector2 SkillCheckUiPos = Vector2(720, 750);
	static constexpr Vector3 OffSet = Vector3(50,50,-30);
	static constexpr float HandleSpeed = 5;				//ハンドルが動くスピード
	static constexpr int FristDurabilityValue = 100;	//耐久力
	static constexpr int AttackDamage = 10;				//攻撃力
	static constexpr int GoodHandleSize = 150;		//グッドの画像横サイズ
	static constexpr int PerfectHandleSize = 30;	//パーフェクトの画像横サイズ

	static constexpr int ConsumptionDurability = 5;	//消耗耐久値

	int m_model;

	int m_durabilityValue;
	int m_attackDamage;
	int m_consumptionDurability;

	bool m_isCutTreeFlag;	//木を伐ったか

	Sprite m_skillCheckUi;				//スキルチェックのバー
	Sprite m_skillCheckHandleUi;		
	Sprite m_checkGoodHandleUi;			//
	Sprite m_checkPerfectHandleUi;		//

	Transform m_skillCheckUiPos;		//スキルチェックのバーの位置
	Transform m_skillCheckHandleUiPos;	//
	Transform m_checkGoodHandleUiPos;	//
	Transform m_checkPerfectHandleUiPos;	//

	LoadPlayer* m_player;
	Camera* m_camera;

	bool m_turnHandleRight;		//ハンドルが右に行くべきか
	bool m_turnHandleLeft;		//ハンドルが左に行くべきか
	bool m_positionDecision;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Ax( LoadPlayer* player, Camera* camera);

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
};