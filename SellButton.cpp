#include "SellButton.h"
#include "LoadPlayer.h"
#include "SceneGame.h"
#include "Inventory.h"
#include "DxLib.h"

#include "Time.h"

SellButton::SellButton(LoadPlayer* player,Inventory* inventory) :
	Actor("SellButton", "sell_button.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&SellButton::OnClick, this)),
	m_checkOnClick(false),
	m_player(player),
	m_inventory(inventory),
	m_checkClick(false),
	m_time(0)
{
}

void SellButton::OnClick()
{
	if (CheckCondition() && m_player->GetNowTrede())
	{
		m_checkOnClick = true;
		m_checkClick = true;
	}
}

void SellButton::Update()
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

void SellButton::Draw()
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

	if (m_player->GetNowTrede())
	{
		//�{���̕`�揈��
		Actor::Draw();
	}

	//�P�x�̐ݒ�����ɖ߂�
	SetDrawBright(255, 255, 255);
}

bool SellButton::CheckCondition()
{
	if (m_inventory->GetHaveWoodCount() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}