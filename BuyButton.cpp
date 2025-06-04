#include "BuyButton.h"
#include "LoadPlayer.h"
#include "SceneGame.h"
#include "Wallet.h"
#include "TredeUi.h"
#include "DxLib.h"

BuyButton::BuyButton(LoadPlayer* player,Wallet* wallet,TredeUi* tredeUi) :
	Actor("SellButton", "sell_button.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&BuyButton::OnClick, this)),
	m_checkOnClick(false),
	m_player(player),
	m_wallet(wallet),
	m_tredeUi(tredeUi)
{
}

void BuyButton::OnClick()
{
	if(CheckCondition()) m_checkOnClick = true;
}

void BuyButton::Update()
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

void BuyButton::Draw()
{
	if (m_player->GetNowTrede())
	{
		//本来の描画処理
		Actor::Draw();
	}
}

bool BuyButton::CheckCondition()
{
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