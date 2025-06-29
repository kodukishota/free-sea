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
	//�[�Ƀn���h����������܂�Ԃ�
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

	//Good��Perfect�̈ʒu�������_���Őݒ�
	if (!m_positionDecision)
	{
		int goodHandlePosIndex = GetRand(GoodHandleUiPosIndex - 1);

		//�O��ƈʒu�����Ȃ��悤��
		if (previousPosIndex == goodHandlePosIndex)
		{
			goodHandlePosIndex = GetRand(GoodHandleUiPosIndex - 1);
		}

		//�O��̈ʒu�̃C���f�N�X�ۑ��p
		previousPosIndex = goodHandlePosIndex;

		//�O�b�h�̈ʒu�ݒ�
		m_checkGoodHandleUiPos.position = SkillCheckUiPos;
		m_checkGoodHandleUiPos.position.x = GoodHandleUiPosX[goodHandlePosIndex];
		//�p�[�t�F�N�g�̈ʒu�ݒ�
		m_checkPerfectHandleUiPos.position = m_checkGoodHandleUiPos.position;

		m_positionDecision = true;
	}

	if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_1))
	{
		//�������ʒu��Good��Perfect�̒��ŉ�����Ă��邩
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
		//Good��Perfect�ȊO�ŉ����ꂽ�Ƃ�
		else
		{
			m_badFlag = true;
		}

		m_positionDecision = false;

		m_isClick = true;
	}
}