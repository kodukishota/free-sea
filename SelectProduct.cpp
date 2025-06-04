#include "SelectProduct.h"
#include "LoadPlayer.h"
#include "SceneGame.h"
#include "Wallet.h"
#include "DxLib.h"

SelectProduct::SelectProduct(LoadPlayer* player,
	Vector2 position,
	int productNum,
	char* iconName) :
	Actor("BuyButton", iconName, position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&SelectProduct::OnClick, this)),
	m_checkOnClick(false),
	m_player(player),
	m_productNum(productNum)
{
}

void SelectProduct::OnClick()
{
	m_checkOnClick = true;
}

void SelectProduct::Update()
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

void SelectProduct::Draw()
{
	if (m_player->GetNowTrede())
	{
		//�{���̕`�揈��
		Actor::Draw();
	}
}