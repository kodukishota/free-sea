#include "Inventory.h"
#include "Screen.h"
#include "ImageLoader.h"
#include "ItemIcon.h"
#include "LoadPlayer.h"
#include "Input.h"
#include "LoadFoodData.h"
#include "EatButton.h"
#include "Seedling.h"
#include "Ax.h"

Inventory::Inventory(LoadPlayer* player, LoadFoodData* loadFoodData, Ax* ax) :
	m_maxHaveItem(10),
	m_haveFoodCount(0),
	m_canGetItem(false),
	m_itemNum(0),
	m_gettingItem(false),
	m_takeFood(0),
	m_eatFoodPosNum(0),
	m_eatFoodFlag(false),
	m_dropItemCompletion(false),
	m_seInventory(0),
	m_fontTextureId(0),
	m_haveWoodCount(0),
	m_player(player),
	m_loadFoodData(loadFoodData),
	m_eatButton(nullptr),
	m_food(),
	m_haveSeedlingCount(0),
	m_ax(ax)
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

	//アイテムを拾うことができるか
	if (m_haveFoodCount < m_maxHaveItem)
	{
		m_canGetItem = true;
	}
	else 
	{
		m_canGetItem = false;
	}

	//メニューを開いた時に持っている木の数を表示してくれるUiの位置を変更
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

	//苗木を植えれる位置に来たら
	if (m_player->GetCanPlantSeedling())
	{
		PlantSeedling();
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

	for (int i = 0; i <= m_haveFoodCount - 1; i++)
	{
		if (m_haveFoodCount != 0)
		{
			if (m_foodList[i]->GetIsSelect())
			{
				m_takeItemTransform.position = m_foodList[i]->GetDrawPos();

				m_takeItemUi.Draw(m_takeItemTransform);
			}
		}
	}

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
		//食べ物のアイコンを生成
		m_food = new Food(foodId,
			m_player,
			&m_loadFoodData->m_foodData[foodId],
			m_haveFoodCount,
			m_eatButton,
			this);

		GetParent()->AddChild(m_food);

		//持っている食べ物リストにいれる
		m_foodList.push_back(m_food);

		m_haveFoodCount++;
	}
}

void Inventory::EatFood()
{
	for (int i = 0; i <= m_haveFoodCount - 1; i++)
	{
		//選択した食べ物を覚えて得ておく
		if (m_foodList[i]->GetIsSelect())
		{
			m_takeFood = i;
			m_eatFoodPosNum = m_foodList[m_takeFood]->GetDrawPosNum();

			if (m_eatButton->GetCheckOnClick())
			{
				//食べるボタンを押したら空腹ゲージを回復
				m_player->EatingFood(m_foodList[m_takeFood]->GetRecoveryHungry());

				m_eatFoodFlag = true;

				//持っている食べ物リストから削除
				m_foodList[m_takeFood]->DestroyFood();
				m_foodList.erase(m_foodList.begin() + m_takeFood);

				m_haveFoodCount--;
			}
		}

		//食べたアイテムより後ろにあるアイコンを前にずらす
		if (m_shiftIconCount >= m_haveFoodCount)
		{
			m_eatFoodFlag = false;
			m_shiftIconCount = 0;
		}
	}
}

void Inventory::PlantSeedling()
{
	//Fを押したら苗木を植える
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_F))
	{
		AddChild(new Seedling(m_ax, m_player, this, m_player->GetPosition()));
	}
}