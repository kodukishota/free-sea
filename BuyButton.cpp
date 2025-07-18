#include "BuyButton.h"
#include "LoadPlayer.h"
#include "SceneGame.h"
#include "Wallet.h"
#include "TredeUi.h"
#include "DxLib.h"
#include "Time.h"

BuyButton::BuyButton(LoadPlayer* player,Wallet* wallet,TredeUi* tredeUi) :
	Actor("BuyButton", "buy_button.png", Position),
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
	//条件を満たしてない場合はボタンを暗化させる
	if (!CheckCondition())
	{
		//以降、輝度を下げて描画する
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

	//本来の描画処理
	if (m_player->GetNowTrede())
	{
		Actor::Draw();
	}

	//輝度の設定を元に戻す
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