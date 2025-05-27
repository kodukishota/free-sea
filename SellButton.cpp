#include "SellButton.h"
#include "SceneGame.h"
#include "DxLib.h"

SellButton::SellButton() :
	Actor("SellButton", "sell_button.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&SellButton::OnClick, this)),
	m_checkOnClick(false)
{
}

void SellButton::OnClick()
{
	m_checkOnClick = true;
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
	//�{���̕`�揈��
	Actor::Draw();
}