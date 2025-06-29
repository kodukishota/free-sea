#include "TredeUi.h"
#include "Input.h"
#include "LoadPlayer.h"
#include "LoadFoodData.h"
#include "SellButton.h"
#include "SelectProduct.h"
#include "Wallet.h"
#include "BuyButton.h"
#include "Inventory.h"
#include "ImageLoader.h"

TredeUi::TredeUi(
	LoadPlayer* player,
	SellButton* sellButton,
	Wallet* wallet,
	Inventory* inventory,
	LoadFoodData* loadFoodData) :
	m_nowTredeFlag(false),
	m_player(player),
	m_sellButton(sellButton),
	m_wallet(wallet),
	m_inventory(inventory),
	m_seSell(0),
	m_selectProductNum(0),
	m_selectFlag(false),
	m_loadFoodData(loadFoodData),
	m_seBuy(0),
	m_tredeUi(0)
{
	m_sprite.Register("background.png");
	m_transform.position = UiPos;

	m_selectProductUi.Register("take_item.png");

	//�w���{�^���̐���
	m_buyButton = new BuyButton(m_player,m_wallet,this);
	AddChild(m_buyButton);

	LoadBuyItem();

	ProductDisplay();
}

void TredeUi::Load()
{
	//se��ݒ�
	m_seSell = LoadSoundMem("Resource/sound/sell_se.mp3");
	ChangeVolumeSoundMem(128, m_seSell);
	m_seBuy = LoadSoundMem("Resource/sound/buy_se.mp3");
	ChangeVolumeSoundMem(128, m_seBuy);

	m_tredeUi = ImageLoader::GetInstance()->Load("trede_ui.png");

	m_sprite.Load();
	m_selectProductUi.Load();
}

void TredeUi::Release()
{
	DeleteSoundMem(m_seSell);
	DeleteSoundMem(m_seBuy);

	ImageLoader::GetInstance()->Delete("trede_ui.png");

	m_sprite.Release();
	m_selectProductUi.Release();
}

void TredeUi::Update()
{
	m_sprite.Update();
	m_selectProductUi.Update();

	m_nowTredeFlag = m_player->GetNowTrede();
	
	//ESCAPE�L�[�ŕ���
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE) && m_nowTredeFlag)
	{
		m_player->ResetNowTrede();
	}

	//�؂𔄂�
	if (m_sellButton->GetCheckOnClick() && m_inventory->GetHaveWoodCount() != 0)
	{
		//���������̃T�E���h���Đ�
		PlaySoundMem(m_seSell, DX_PLAYTYPE_BACK);

		m_wallet->InWalletMoney(10);

		m_inventory->LostHaveWood(1);
	}
	

	if (m_nowTredeFlag)
	{
		BuyProduct();
	}
}

void TredeUi::Draw()
{
	if (m_nowTredeFlag)
	{
		m_sprite.Draw(m_transform);

		//�I��ł��鏤�i�̏���`��
		if (m_selectFlag)
		{
			SetFontSize(30);

			DrawString(800, 300,
				m_productData[m_selectProductNum].m_itemName,
				GetColor(255, 255, 255));

			DrawFormatString(800, 400, GetColor(255, 255, 255),
				"�K�v���z %d $",
				m_productData[m_selectProductNum].m_needMoney); 

			DrawString(800, 500,
				m_productData[m_selectProductNum].m_flavorText,
				GetColor(255, 255, 255));

			m_selectProductUi.Draw
			(m_selectProduct[m_selectProductNum]->GetTransform());
		}
	}

	//�߂��Ȃ������������`��
	if (m_player->CanInteractObject(m_trederPos, CanTredeRange))
	{
		if (!m_player->GetIsMenu() && !m_player->GetNowTrede())
		{
			DrawGraph(static_cast<int>(TredeUiPos.x), static_cast<int>(TredeUiPos.y), m_tredeUi, true);
		}
	}
}

//�w���ł���A�C�e���̃��[�h
void TredeUi::LoadBuyItem()
{
	int fileHandle = FileRead_open("product.csv");

	char dontUseLine[9][256];

	for (int i = 0; i < 1; i++) FileRead_gets(dontUseLine[0], 256, fileHandle);

	for (int i = 0; i <= static_cast<int>(TredeItem::Length) - 1; i++)
	{
		FileRead_scanf(fileHandle, "%[^,],%[^,],%[^,],%d,%d,%d",
			m_productData[i].m_itemName, m_productData[i].m_iconName,m_productData[i].m_flavorText, 
			&m_productData[i].m_needMoney,&m_productData[i].m_productId,&m_productData[i].m_productKindId);//�ǂݍ���
	}

	//�t�@�C�������
	FileRead_close(fileHandle);
}

//���i����ׂ�
void TredeUi::ProductDisplay()
{
	m_productTransform.position = ProductUiPos;

	for (int i = 0; i <= static_cast<int>(TredeItem::Length) - 1; i++)
	{
		m_selectProduct[i] = new SelectProduct(
			m_player,
			m_productTransform.position,
			i,
			m_productData[i].m_iconName);

		AddChild(m_selectProduct[i]);

		m_productTransform.position += Vector2(0, 100);

		m_displayCount++;

		//���i����s���ׂ��玟�̒i�ɍs��
		if (m_displayCount >= 7)
		{
			m_productTransform.position.y = ProductUiPos.y;

			m_productTransform.position += Vector2(150, 0);

			m_displayCount = 0;
		}
	}
}

//���i�𔃂�
void TredeUi::BuyProduct()
{
	//���i�̃A�C�R�����N���b�N������I�ׂ�
	for (int i = 0; i <= static_cast<int>(TredeItem::Length) - 1; i++)
	{
		if (m_selectProduct[i]->GetCheckOnClick())
		{
			m_selectProductNum = m_selectProduct[i]->GetProductNum();

			//���i�̕ۑ�
			m_selectProductValue = m_productData[m_selectProductNum].m_needMoney;

			m_selectFlag = true;
		}
	}
	//���i��I�񂾏�Ԃōw���{�^������������w��
	if (m_buyButton->GetCheckOnClick())
	{
		//�������Ƃ��̃T�E���h�Đ�
		PlaySoundMem(m_seBuy, DX_PLAYTYPE_BACK);
		//�����̏���
		m_wallet->LostMoney(m_productData[m_selectProductNum].m_needMoney);

		if (m_productData[m_selectProductNum].m_productKindId == 0)
		{
			//�������H�ו��̃A�C�R����ݒ肵����
			m_inventory->BuyFood(m_productData[m_selectProductNum].m_productId);
		}
		if (m_productData[m_selectProductNum].m_productKindId == 1)
		{
			m_inventory->BuyAx(m_productData[m_selectProductNum].m_productId);
		}
		if (m_productData[m_selectProductNum].m_productKindId == 2)
		{
			m_inventory->BuySeedling();
		}
	}
}