#include "SkillCheak.h"
#include "LoadPlayer.h"
#include "Input.h"

SkillCheck::SkillCheck(LoadPlayer* player) : Node(),
m_turnHandleRight(true),
m_turnHandleLeft(false),
m_positionDecision(false),
m_player(player),
m_prefectFlag(false),
m_goodFlag(false),
m_badFlag(false),
m_isClick(false)
{
	m_skillCheckUi.Register("check_bar_ui.png");
	m_skillCheckHandleUi.Register("check_handle.png");
	m_checkGoodHandleUi.Register("check_good_handle.png");
	m_checkPerfectHandleUi.Register("check_perfect_handle.png");
	m_skillCheckUiPos.position = SkillCheckUiPos;
	m_skillCheckHandleUiPos.position = SkillCheckUiPos;
}

void SkillCheck::Load()
{
	m_skillCheckUi.Load();
	m_skillCheckHandleUi.Load();
	m_checkGoodHandleUi.Load();
	m_checkPerfectHandleUi.Load();
}

void SkillCheck::Release()
{
	m_skillCheckUi.Release();
	m_skillCheckHandleUi.Release();
	m_checkGoodHandleUi.Release();
	m_checkPerfectHandleUi.Release();
}

void SkillCheck::Update()
{
	if (m_player->GetCutTree() && !m_player->GetDontHaveAx())
	{
		CutTreeSkillCheck();
	}

	m_skillCheckUi.Update();
	m_skillCheckHandleUi.Update();
	m_checkGoodHandleUi.Update();
	m_checkPerfectHandleUi.Update();
}

void SkillCheck::Draw()
{
	if (m_player->GetCutTree() && !m_player->GetDontHaveAx())
	{
		m_skillCheckUi.Draw(m_skillCheckUiPos);
		m_checkGoodHandleUi.Draw(m_checkGoodHandleUiPos);
		m_checkPerfectHandleUi.Draw(m_checkPerfectHandleUiPos);
		m_skillCheckHandleUi.Draw(m_skillCheckHandleUiPos);
	}
}

void SkillCheck::CutTreeSkillCheck()
{
	//端にハンドルが来たら折り返す
	if (SkillCheckUiPos.x + SkillCheckUiPos.x / 2
		<= m_skillCheckHandleUiPos.position.x)
	{
		m_turnHandleLeft = true;
		m_turnHandleRight = false;
	}
	else if (SkillCheckUiPos.x - SkillCheckUiPos.x / 2
		>= m_skillCheckHandleUiPos.position.x)
	{
		m_turnHandleLeft = false;
		m_turnHandleRight = true;
	}

	if (m_turnHandleLeft)
	{
		m_skillCheckHandleUiPos.position.x -= HandleSpeed;
	}
	else if (m_turnHandleRight)
	{
		m_skillCheckHandleUiPos.position.x += HandleSpeed;
	}

	int previousPosIndex = 0;

	//GoodやPerfectの位置をランダムで設定
	if (!m_positionDecision)
	{
		int goodHandlePosIndex = GetRand(GoodHandleUiPosIndex - 1);

		//前回と位置が被らないように
		if (previousPosIndex == goodHandlePosIndex)
		{
			goodHandlePosIndex = GetRand(GoodHandleUiPosIndex - 1);
		}

		//前回の位置のインデクス保存用
		previousPosIndex = goodHandlePosIndex;

		//グッドの位置設定
		m_checkGoodHandleUiPos.position = SkillCheckUiPos;
		m_checkGoodHandleUiPos.position.x = GoodHandleUiPosX[goodHandlePosIndex];
		//パーフェクトの位置設定
		m_checkPerfectHandleUiPos.position = m_checkGoodHandleUiPos.position;

		m_positionDecision = true;
	}

	if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_1))
	{
		//押した位置がGoodやPerfectの中で押されているか
		if (m_checkPerfectHandleUiPos.position.x + PerfectHandleSize / 2 >= m_skillCheckHandleUiPos.position.x &&
			m_checkPerfectHandleUiPos.position.x - PerfectHandleSize / 2 <= m_skillCheckHandleUiPos.position.x)
		{
			m_prefectFlag = true;
		}
		else if (m_checkGoodHandleUiPos.position.x + GoodHandleSize / 2 >= m_skillCheckHandleUiPos.position.x &&
			m_checkGoodHandleUiPos.position.x - GoodHandleSize / 2 <= m_skillCheckHandleUiPos.position.x)
		{
			m_goodFlag = true;
		}
		//GoodやPerfect以外で押されたとき
		else
		{
			m_badFlag = true;
		}

		m_positionDecision = false;

		m_isClick = true;
	}
}