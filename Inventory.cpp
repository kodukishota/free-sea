#include "Inventory.h"
#include "Screen.h"
#include "ImageLoader.h"
#include "ItemIcon.h"
#include "LoadPlayer.h"
#include "Input.h"
#include "LoadFoodData.h"
#include "EatButton.h"

Inventory::Inventory(LoadPlayer* player, LoadFoodData* loadFoodData) :
	m_maxHaveItem(10),
	m_haveFoodCount(0),
	m_canGetItem(false),
	m_itemNum(0),
	m_gettingItem(false),
	m_takeFood(0),
	m_dropItem(false),
	m_dropItemNum(0),
	m_dropItemCompletion(false),
	m_seInventory(0),
	m_fontTextureId(0),
	m_haveWoodCount(0),
	m_player(player),
	m_loadFoodData(loadFoodData),
	m_eatButton(nullptr)
{
	m_axInventoryUi.Register("inventory_ui1.png");
	m_foodInventoryUi.Register("inventory_ui1.png");
	m_takeItemUi.Register("take_item.png");
	m_woodIcon.Register("wood_icon.png");

	m_eatButton = new EatButton(m_player);
	AddChild(m_eatButton);
}

void Inventory::Load()
{
	//seを設定
	m_seInventory = LoadSoundMem("Resource/sound/move_takeUi.mp3");
	ChangeVolumeSoundMem(128, m_seInventory);

	m_fontTextureId = ImageLoader::GetInstance()->Load("score_font.png");

	m_axInventoryUi.Load();
	m_foodInventoryUi.Load();
	m_takeItemUi.Load();
	m_woodIcon.Load();
}

void Inventory::Release()
{
	DeleteSoundMem(m_seInventory);

	ImageLoader::GetInstance()->Delete("score_font.png");

	m_axInventoryUi.Release();
	m_foodInventoryUi.Release();
	m_takeItemUi.Release();
	m_woodIcon.Release();
}

void Inventory::Update()
{
	m_axInventoryUi.Update();
	m_foodInventoryUi.Update();
	m_takeItemUi.Update();
	m_woodIcon.Update();

	if (m_dropItem)
	{
		m_dropItem = false;
	}
	if (m_gettingItem)
	{
		m_gettingItem = false;
	}

	//アイテムを拾うことができるか
	if (m_haveFoodCount < m_maxHaveItem)
	{
		m_canGetItem = true;
	}
	else 
	{
		m_canGetItem = false;
	}

	if (!m_player->GetIsMenu())
	{
		m_haveWoodTransform.position = WoodIconPos;
	}
	else
	{
		m_haveWoodTransform.position = WoodMenuIconPos;
	}

	
	if (m_haveFoodCount != 0)
	{
	
		EatFood();
	}

}

void Inventory::Draw()
{
	//斧インベントリの枠の描画
	for (int i = 0; i <= MaxHaveAx - 1; i++)
	{
		m_axInventoryPos.position = AxInventoryUiPos + Vector2(SquareSize * i, 0);

		if (m_player->GetIsMenu())
		{
			m_axInventoryPos.position = AxMenuInventoryUiPos + Vector2(SquareSize * i, 0);
		}

		m_axInventoryUi.Draw(m_axInventoryPos);
	}

	//食べ物インベントリの枠の描画
	for (int i = 0; i <= MaxhaveFood - 1; i++)
	{
		m_foodInventoryPos.position = FoodInventoryUiPos + Vector2(SquareSize * i, 0);

		if (m_player->GetIsMenu())
		{
			m_foodInventoryUi.Draw(m_foodInventoryPos);
		}
	}
	m_takeItemUi.Draw(m_takeItemTransform);

	//持っている木の描画
	m_woodIcon.Draw(m_haveWoodTransform);

	//現在の持っている木の数を描画
	Vector2 nowHaveWoodCountUiPos = m_haveWoodTransform.position + Vector2(110, -23);
	nowHaveWoodCountUiPos.y += FontMargin;
	int nowHaveWoodCount = m_haveWoodCount;
	int nowhaveWoodDigit = 1;
	do
	{
		int value = nowHaveWoodCount % 10;	// 1の位の値を取り出す

		DrawRectGraph(
			static_cast<int>(nowHaveWoodCountUiPos.x - FontSize.x * nowhaveWoodDigit), static_cast<int>(nowHaveWoodCountUiPos.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		nowHaveWoodCount /= 10;
		nowhaveWoodDigit++;		// 次の桁へ
	} while (nowHaveWoodCount > 0);
}

void Inventory::CreateFoodIcon(int foodId)
{
	if (m_haveFoodCount <= m_maxHaveItem)
	{
		m_food[m_haveFoodCount] = new Food(foodId,
			m_player,
			&m_loadFoodData->m_foodData[foodId],
			m_haveFoodCount,
			m_eatButton);

		GetParent()->AddChild(m_food[m_haveFoodCount]);

		m_haveFoodCount++;
	}
}

void Inventory::EatFood()
{
	for (int i = 0; i <= m_haveFoodCount - 1; i++)
	{
		if (m_food[i]->GetIsSelect())
		{
			m_takeFood = i;

			if (m_eatButton->GetCheckOnClick())
			{
				m_player->EatingFood(m_food[m_takeFood]->GetRecoveryHungry());

				m_food[m_takeFood]->DestroyFood();
				m_haveFoodCount--;
			}
		}
	}
}