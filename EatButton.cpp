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
	//本来の更新処理
	Actor::Update();
	if (m_checkOnClick)
	{
		m_checkOnClick = false;
	}

	//ボタン
	m_button.Update(m_transform.position);
}

void EatButton::Draw()
{
	if (m_player->GetIsMenu())
	{
		//本来の描画処理
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