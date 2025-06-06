#include "TredeUi.h"
#include "Input.h"
#include "LoadPlayer.h"
#include "LoadFoodData.h"
#include "SellButton.h"
#include "SelectProduct.h"
#include "Wallet.h"
#include "BuyButton.h"
#include "Inventory.h"

TredeUi::TredeUi(LoadPlayer* player,
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
	m_loadFoodData(loadFoodData)
{
	m_sprite.Register("background.png");
	m_transform.position = UiPos;

	//購入ボタンの生成
	m_buyButton = new BuyButton(m_player,m_wallet,this);
	AddChild(m_buyButton);

	LoadBuyItem();

	ProductDisplay();
}

void TredeUi::Load()
{
	//seを設定
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
	
	//ESCAPEキーで閉じる
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE) && m_nowTredeFlag)
	{
		m_player->ResetNowTrede();
	}

	//木を売る
	if (m_sellButton->GetCheckOnClick() && m_inventory->GetHaveWoodCount() != 0)
	{
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

		//選んでいる商品の情報を描画
		if (m_selectFlag)
		{
			SetFontSize(30);

			DrawString(1000, 300,
				m_productData[m_selectProductNum].m_itemName,
				GetColor(255, 255, 255));

			DrawFormatString(1000, 400, GetColor(255, 255, 255),
				"必要金額 %d $",
				m_productData[m_selectProductNum].m_needMoney); 

			DrawString(1000, 500,
				m_productData[m_selectProductNum].m_flavorText,
				GetColor(255, 255, 255));
		}
	}
}

//購入できるアイテムのロード
void TredeUi::LoadBuyItem()
{
	int fileHandle = FileRead_open("product.csv");

	char dontUseLine[9][256];

	for (int i = 0; i < 1; i++) FileRead_gets(dontUseLine[0], 256, fileHandle);

	for (int i = 0; i <= static_cast<int>(TredeItem::Length) - 1; i++)
	{
		FileRead_scanf(fileHandle, "%[^,],%[^,],%[^,],%d,%d",
			m_productData[i].m_itemName, m_productData[i].m_iconName,
			m_productData[i].m_flavorText, &m_productData[i].m_needMoney,&m_productData[i].m_productId);//読み込み
	}

	//ファイルを閉じる
	FileRead_close(fileHandle);
}

//商品を並べる
void TredeUi::ProductDisplay()
{
	//m_productUi.Register(m_productData->m_iconName);

	m_productTransform.position = ProductUiPos;

	for (int i = 0; i <= static_cast<int>(TredeItem::Length) - 1; i++)
	{

		m_selectProduct[i] = new SelectProduct(
			m_player,
			m_productTransform.position,
			i,
			m_productData[i].m_iconName);

		AddChild(m_selectProduct[i]);

		m_productTransform.position += Vector2(0, 90);
	}
}

//商品を買う
void TredeUi::BuyProduct()
{
	//商品のアイコンをクリックしたら選べる
	for (int i = 0; i <= static_cast<int>(TredeItem::Length) - 1; i++)
	{
		if (m_selectProduct[i]->GetCheckOnClick())
		{
			m_selectProductNum = m_selectProduct[i]->GetProductNum();

			m_selectFlag = true;
		}
	}
	//商品を選んだ状態で購入ボタンを押したら購入
	if (m_buyButton->GetCheckOnClick())
	{
		m_wallet->LostMoney(m_productData[m_selectProductNum].m_needMoney);

		m_inventory->CreateFoodIcon(m_productData[m_selectProductNum].m_productId);		
	}
}