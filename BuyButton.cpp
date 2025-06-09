#include "BuyButton.h"
#include "LoadPlayer.h"
#include "SceneGame.h"
#include "Wallet.h"
#include "TredeUi.h"
#include "DxLib.h"
#include "Time.h"

BuyButton::BuyButton(LoadPlayer* player,Wallet* wallet,TredeUi* tredeUi) :
	Actor("SellButton", "sell_button.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&BuyButton::OnClick, this)),
	m_checkOnClick(false),
	m_player(player),
	m_wallet(wallet),
	m_tredeUi(tredeUi),
	m_needMoney(0),
	m_time(0),
	m_checkClick(0)
{
}

void BuyButton::OnClick()
{
	if (CheckCondition() && m_player->GetNowTrede())
	{
		m_checkOnClick = true;
		m_checkClick = true;
	}
}

void BuyButton::Update()
{
	//–{—ˆ‚ÌXVˆ—
	Actor::Update();

	if (m_checkOnClick)
	{
		m_checkOnClick = false;
	}

	//ƒ{ƒ^ƒ“
	m_button.Update(m_transform.position);
}

void BuyButton::Draw()
{
	//ğŒ‚ğ–‚½‚µ‚Ä‚È‚¢ê‡‚Íƒ{ƒ^ƒ“‚ğˆÃ‰»‚³‚¹‚é
	if (!CheckCondition())
	{
		//ˆÈ~A‹P“x‚ğ‰º‚°‚Ä•`‰æ‚·‚é
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

	//–{—ˆ‚Ì•`‰æˆ—
	if (m_player->GetNowTrede())
	{
		Actor::Draw();
	}

	//‹P“x‚Ìİ’è‚ğŒ³‚É–ß‚·
	SetDrawBright(255, 255, 255);
}

bool BuyButton::CheckCondition()
{
	m_needMoney = m_tredeUi->GetSelectProductValue();

	if (m_tredeUi->GetSelectFlag())
	{
		if (m_wallet->HaveMoney() >= m_needMoney)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}