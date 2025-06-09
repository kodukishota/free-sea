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

	if (m_player->GetIsMenu())
	{
		//本来の描画処理
		Actor::Draw();
	}

	//輝度の設定を元に戻す
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