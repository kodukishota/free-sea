#include "EatButton.h"
#include "LoadPlayer.h"
#include "SceneGame.h"
#include "DxLib.h"

EatButton::EatButton(LoadPlayer* player) :
	Actor("SellButton", "sell_button.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&EatButton::OnClick, this)),
	m_checkOnClick(false),
	m_player(player)
{
}

void EatButton::OnClick()
{
	if (CheckCondition()) m_checkOnClick = true;
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
	if (m_player->GetIsMenu())
	{
		//�{���̕`�揈��
		Actor::Draw();
	}
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