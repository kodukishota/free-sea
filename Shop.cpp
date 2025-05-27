#include "Shop.h"
#include "Chest.h"
#include "Wallet.h"
#include "SellButton.h"
#include "ImageLoader.h"

Shop::Shop(Chest* chest,Wallet* wallet,SellButton* sellButton) :
	m_chest(chest),
	m_isSellItem(false),
	m_wallet(wallet),
	m_sellButton(sellButton),
	m_takeItem(0),
	m_dontSellFlag(false),
	m_seSell(0)
{
	//Ui�̓o�^
	m_shopUi.Register("shop_ui.png");

	m_shopTransform.position = ShopUiPos;
}

void Shop::Load()
{
	//se��ݒ�
	m_seSell = LoadSoundMem("Resource/sound/sell_se.mp3");
	ChangeVolumeSoundMem(128, m_seSell);

	m_shopUi.Load();
}

void Shop::Release()
{
	DeleteSoundMem(m_seSell);
	m_shopUi.Release();
}

void Shop::Update()
{
	m_shopUi.Update();	

	m_takeItem = m_chest->GetTakeItem();	

	if (m_sellButton->GetCheckOnClick() && !m_chest->GetItemList().empty())
	{	
		m_wallet->InWalletMoney(std::next(m_chest->GetItemList().begin(), m_takeItem)->GetSellMoney());

		m_chest->LostItem(m_chest->GetTakeItem());

		PlaySoundMem(m_seSell, DX_PLAYTYPE_BACK);
	}
}

void Shop::Draw()
{
	m_shopUi.Draw(m_shopTransform);
	

	SetFontSize(30);

	DrawString(5, 920,
		"WASD:�ړ��@R:�C���x���g������`�F�X�g�ց@C:����؂�ւ��@M:���j���[����",
		GetColor(255, 255, 255));

	if (!m_chest->GetItemList().empty())
	{

		DrawString(920, 70,
			"�A�C�e����"
			, GetColor(255, 255, 255));
		DrawString(920, 100,
			std::next(m_chest->GetItemList().begin(), m_chest->GetTakeItem())->GetItemName()
			, GetColor(255, 255, 255));

		DrawFormatString(920, 200,
			GetColor(255, 255, 255),
			"���z\n%d $", 
			std::next(m_chest->GetItemList().begin(), m_chest->GetTakeItem())->GetSellMoney());

		DrawFormatString(920, 300,
			GetColor(255, 255, 255),
			"�d��\n%d kg",
			std::next(m_chest->GetItemList().begin(), m_chest->GetTakeItem())->GetItemWeight());

		SetFontSize(20);
		DrawString(920, 400,
			std::next(m_chest->GetItemList().begin(), m_chest->GetTakeItem())->GetFlavorText()
			, GetColor(255, 255, 255));
	}
}