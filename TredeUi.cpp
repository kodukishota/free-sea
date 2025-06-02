#include "TredeUi.h"
#include "Input.h"
#include "LoadPlayer.h"
#include "SellButton.h"
#include "Wallet.h"
#include "Inventory.h"

TredeUi::TredeUi(LoadPlayer* player, SellButton* sellButton, Wallet* wallet, Inventory* inventory) :
	m_nowTredeFlag(false),
	m_player(player),
	m_sellButton(sellButton),
	m_wallet(wallet),
	m_inventory(inventory),
	m_seSell(0)
{
	m_sprite.Register("shop_ui.png");
	m_transform.position = UiPos;
}

void TredeUi::Load()
{
	//se‚ðÝ’è
	m_seSell = LoadSoundMem("Resource/sound/sell_se.mp3");
	ChangeVolumeSoundMem(128, m_seSell);

	m_sprite.Load();
}

void TredeUi::Release()
{
	DeleteSoundMem(m_seSell);
	m_sprite.Release();
}


void TredeUi::Update()
{
	m_sprite.Update();


	m_nowTredeFlag = m_player->GetNowTrede();
	
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE) && m_nowTredeFlag)
	{
		m_player->ResetNowTrede();
	}

	if (m_sellButton->GetCheckOnClick() && m_inventory->GetHaveWoodCount() != 0)
	{
		m_wallet->InWalletMoney(10);

		m_inventory->LostHaveWood(1);
	}

}

void TredeUi::Draw()
{
	if (m_nowTredeFlag)
	{
		m_sprite.Draw(m_transform);
	}
}

void TredeUi::LoadBuyItem()
{
	
}