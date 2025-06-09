#include "EatButton.h"
#include "LoadPlayer.h"
#include "SceneGame.h"
#include "Time.h"
#include "DxLib.h"

EatButton::EatButton(LoadPlayer* player) :
	Actor("SellButton", "sell_button.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&EatButton::OnClick, this)),
	m_checkOnClick(false),
	m_player(player),
	m_time(0),
	m_checkClick(0)
{
}

void EatButton::OnClick()
{
	if (CheckCondition() && m_player->GetIsMenu())
	{
		m_checkOnClick = true;
		m_checkClick = true;
	}
}

void EatButton::Update()
{
	//�{���̍X�V����
	Actor::Update();
	if (m_checkOnClick)
	{
		m_checkOnClick = false;
	}

	//�{�^��
	m_button.Update(m_transform.position);
}

void EatButton::Draw()
{
	//�����𖞂����ĂȂ��ꍇ�̓{�^�����É�������
	if (!CheckCondition())
	{
		//�ȍ~�A�P�x�������ĕ`�悷��
		SetDrawBright(50, 50, 50);
	}

	if (m_checkClick)
	{
		m_time += Time::GetInstance()->GetDeltaTime();

		if (m_time <= 0.2f)
		{
			SetDrawBright(50, 50, 50);
		}
		else
		{
			m_time = 0;

			m_checkClick = false;
		}
	}

	if (m_player->GetIsMenu())
	{
		//�{���̕`�揈��
		Actor::Draw();
	}

	//�P�x�̐ݒ�����ɖ߂�
	SetDrawBright(255, 255, 255);
}

bool EatButton::CheckCondition()
{
	if (m_player->GetHungerLevel() >= m_player->GetMaxHungerLevel())
	{
		return false;
	}
	else
	{
		return true;
	}
}