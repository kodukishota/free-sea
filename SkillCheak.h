#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Sprite.h"

class LoadPlayer;

class SkillCheck : public Node
{
private:
	static constexpr int GoodHandleUiPosIndex = 9;
	//グッドの位置
	static constexpr int GoodHandleUiPosX[GoodHandleUiPosIndex] = { 420,495,570,645,720,795,870,945,1020 };
	static constexpr Vector2 SkillCheckUiPos = Vector2(720, 750);
	static constexpr int GoodHandleSize = 150;		//グッドの画像横サイズ
	static constexpr int PerfectHandleSize = 30;	//パーフェクトの画像横サイズ
	static constexpr float HandleSpeed = 5;				//ハンドルが動くスピード

	Sprite m_skillCheckUi;				//スキルチェックのバー
	Sprite m_skillCheckHandleUi;
	Sprite m_checkGoodHandleUi;			//
	Sprite m_checkPerfectHandleUi;		//

	Transform m_skillCheckUiPos;		//スキルチェックのバーの位置
	Transform m_skillCheckHandleUiPos;	//
	Transform m_checkGoodHandleUiPos;	//
	Transform m_checkPerfectHandleUiPos;	//

	bool m_turnHandleRight;		//ハンドルが右に行くべきか
	bool m_turnHandleLeft;		//ハンドルが左に行くべきか
	bool m_positionDecision;

	bool m_prefectFlag;
	bool m_goodFlag;
	bool m_badFlag;

	bool m_isClick;

	LoadPlayer* m_player;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	SkillCheck(LoadPlayer* player);

	void CutTreeSkillCheck();

	bool GetPrefectFlag()
	{
		return m_prefectFlag;
	}

	bool GetGoodFlag()
	{
		return m_goodFlag;
	}

	bool GetBadFlag()
	{
		return m_badFlag;
	}

	bool GetIsClick()
	{
		return m_isClick;
	}

	void ResetPrefectFlag()
	{
		m_prefectFlag = false;
	}

	void ResetGoodFlag()
	{
		m_goodFlag = false;
	}

	void ResetBadFlag()
	{
		m_prefectFlag = false;
	}

	void ResetIsClick()
	{
		m_isClick = false;
	}
};