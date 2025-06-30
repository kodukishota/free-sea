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

Inventory::Inventory(LoadPlayer* player, LoadFoodData* loadFoodData, SkillCheck* skillCheck) :
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
	m_ax(nullptr),
	m_shiftIconCount(0),
	m_seEat(0),
	m_skillCheck(skillCheck),
	m_takeAx(0),
	m_breakAx(false)
{
	m_axInventoryUi.Register("inventory_ui.png");
	m_foodInventoryUi.Register("inventory_ui.png");
	m_takeItemUi.Register("take_item.png");

	m_eatButton = new EatButton(m_player);
	AddChild(m_eatButton);

	BuyAx(0);
	BuyAx(0);
}

void Inventory::Load()
{
	//seを設定
	m_seInventory = LoadSoundMem("Resource/sound/move_takeUi.mp3");
	ChangeVolumeSoundMem(128, m_seInventory);
	m_seEat = LoadSoundMem("Resource/sound/eat_se.mp3");
	ChangeVolumeSoundMem(128, m_seEat);

	m_fontTextureId = ImageLoader::GetInstance()->Load("score_font.png");

	m_seedlingIcon = ImageLoader::GetInstance()->Load("seedling_icon.png");
	m_woodIcon = ImageLoader::GetInstance()->Load("wood_icon.png");

	m_axInventoryUi.Load();
	m_foodInventoryUi.Load();
	m_takeItemUi.Load();
}

void Inventory::Release()
{
	DeleteSoundMem(m_seInventory);
	DeleteSoundMem(m_seEat);

	ImageLoader::GetInstance()->Delete("score_font.png");

	ImageLoader::GetInstance()->Delete("seedling_icon.png");
	ImageLoader::GetInstance()->Delete("wood_icon.png");

	m_axInventoryUi.Release();
	m_foodInventoryUi.Release();
	m_takeItemUi.Release();
}

void Inventory::Update()
{
	m_axInventoryUi.Update();
	m_foodInventoryUi.Update();
	m_takeItemUi.Update();

	//アイテムを買うことができるか
	if (m_haveFoodCount < m_maxHaveItem)
	{
		m_canGetItem = true;
	}
	else 
	{
		m_canGetItem = false;
	}

	//メニューを開いた時に斧、持っている木の数を表示してくれるUiの位置を変更
	if (!m_player->GetIsMenu())
	{
		SelectAx();

		m_woodIconPos = WoodIconPos;

		m_seedlingIconPos = SeedlingIconPos;
	}
	else
	{
		m_woodIconPos = MenuWoodIconPos;

		m_seedlingIconPos = MenuSeedlingIconPos;
	}

	if (m_haveFoodCount != 0)
	{
		EatFood();
	}
	else
	{
		m_selectFood = false;
	}

	if (!m_axList.empty())
	{
		BreakAx();

		if (m_player->GetCutTree())
		{
			m_axList[m_takeAx]->CutTree();
		}

		m_player->SetDontHaveAx(false);
	}
	else
	{
		m_player->SetDontHaveAx(true);
		m_player->FellDownTree();
	}

#ifdef _DEBUG

	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_8))
	{
		m_haveWoodCount += 10;
	}
#endif // _DEBUG
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

	//選んでいる食べ物が何かの協調枠の表示
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

	//選んでいる斧が何かの協調枠の表示
	for (int i = 0; i <= m_haveAxCount - 1; i++)
	{
		if (m_haveAxCount != 0)
		{
			m_takeItemTransform.position = m_axList[m_takeAx]->GetDrawPos();

			m_takeItemUi.Draw(m_takeItemTransform);
		}
	}

	//現在の持っている苗木の数を描画
	Vector2 nowHaveSeedlingUiPos = m_seedlingIconPos + Vector2(180, 15);
	nowHaveSeedlingUiPos.y += FontMargin;
	int nowHaveSeedlingCount = m_haveSeedlingCount;
	int nowHaveSeedlingDigit = 1;
	do
	{
		int value = nowHaveSeedlingCount % 10;	// 1の位の値を取り出す

		DrawRectGraph(
			static_cast<int>(nowHaveSeedlingUiPos.x - FontSize.x * nowHaveSeedlingDigit), static_cast<int>(nowHaveSeedlingUiPos.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		nowHaveSeedlingCount /= 10;
		nowHaveSeedlingDigit++;		// 次の桁へ
	} while (nowHaveSeedlingCount > 0);

	//現在の持っている木の数を描画
	Vector2 nowHaveWoodCountUiPos = m_woodIconPos + Vector2(180, 15);
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

	//選択している食べ物の情報を描画
	if (m_selectFood)
	{
		SetFontSize(30);

		DrawString(600, 300,
			m_foodList[m_takeFood]->GetFoodName(),
			GetColor(255, 255, 255));

		DrawString(600, 400,
			m_foodList[m_takeFood]->GetFlavorText(),
			GetColor(255, 255, 255));
	}

	DrawGraph(m_woodIconPos.x, m_woodIconPos.y, m_woodIcon,true);
	DrawGraph(m_seedlingIconPos.x, m_seedlingIconPos.y, m_seedlingIcon,true);
}

void Inventory::BuyFood(int foodId)
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

		AddChild(m_food);

		//持っている食べ物リストにいれる
		m_foodList.push_back(m_food);

		m_haveFoodCount++;
	}
}

void Inventory::BuyAx(int axId)
{
	m_ax = new Ax(m_player, m_skillCheck,m_haveAxCount,axId,this);

	AddChild(m_ax);

	//斧リストにいれる
	m_axList.push_back(m_ax);

	m_haveAxCount++;
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

			m_selectFood = true;

			if (m_eatButton->GetCheckOnClick())
			{
				PlaySoundMem(m_seEat, DX_PLAYTYPE_BACK);

				//食べるボタンを押したら空腹ゲージを回復
				m_player->EatingFood(m_foodList[m_takeFood]->GetRecoveryHungry());

				m_eatFoodFlag = true;

				//持っている食べ物リストから削除
				m_foodList[m_takeFood]->DestroyFood();
				m_foodList.erase(m_foodList.begin() + m_takeFood);

				m_haveFoodCount--;

				m_selectFood = false;
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

void Inventory::SelectAx()
{
	m_takeAx += Input::GetInstance()->GetMouseWheelRot();

	//持っている斧より次を選択できないように
	if (m_takeAx > m_haveAxCount - 1)
	{
		m_takeAx = 0;
	}
	if (m_takeAx < 0)
	{
		m_takeAx = m_haveAxCount - 1;
	}
}

void Inventory::BreakAx()
{
	for (int i = 0; i <= m_haveAxCount - 1; i++)
	{
		if (m_axList[i]->GetDurability() <= 0 && !m_breakAx)
		{
			if (m_haveAxCount <= 1)
			{
				m_player->FellDownTree();
			}

			m_axList[i]->MyDestroy();

			m_axList.erase(m_axList.begin() + i);

			m_haveAxCount--;

			m_breakAx = true;
		}

		//壊れた斧の後ろあったアイコンを前にずらす
		if (m_shiftIconCount >= m_haveAxCount)
		{
			m_breakAx = false;
			m_shiftIconCount = 0;
		}
	}
}