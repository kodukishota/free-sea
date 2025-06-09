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
	//本来の更新処理
	Actor::Update();
	if (m_checkOnClick)
	{
		m_checkOnClick = false;
	}

	//ボタン
	m_button.Update(m_transform.position);
}

void SellButton::Draw()
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

	if (m_player->GetNowTrede())
	{
		//本来の描画処理
		Actor::Draw();
	}

	//輝度の設定を元に戻す
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