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
	//�{���̍X�V����
	Actor::Update();

	if (m_checkOnClick)
	{
		m_checkOnClick = false;
	}

	//�{�^��
	m_button.Update(m_transform.position);
}

void BuyButton::Draw()
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

	//�{���̕`�揈��
	if (m_player->GetNowTrede())
	{
		Actor::Draw();
	}

	//�P�x�̐ݒ�����ɖ߂�
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