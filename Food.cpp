#include "Food.h"
#include "DxLib.h"
#include "LoadPlayer.h"
#include "Input.h"
#include "EatButton.h"
#include "Inventory.h"
#include <cmath>

Food::Food(int foodNum, 
	LoadPlayer* player,
	FoodData* foodData,
	int drawPosNum,
	EatButton* eatButton,
	Inventory* inventory) :
	m_flavorText(),
	m_foodData(*foodData),
	m_foodNumber(foodNum),
	m_player(player),
	m_foodName(),
	m_mouseX(0),
	m_mouseY(0),
	m_eatButton(eatButton),
	m_isSelect(false),
	m_drawPosNum(drawPosNum),
	m_inventory(inventory)
{
	//名前の設定
	m_foodName = m_foodData.m_foodName;
	//フレーバーテキストの設定
	m_flavorText = m_foodData.m_flavorText;
	
	m_iconUi.Register(m_foodData.m_iconName);

	m_recoveryHungry = m_foodData.m_recoveryHungry;

	m_iconPos.position = IconPos;
	m_iconPos.position.x += IconSize.x * m_drawPosNum;
}

void Food::Load()
{
	m_iconUi.Load();
}

void Food::Release()
{
	m_iconUi.Release();
}

void Food::Update()
{
	m_iconUi.Update();
	

	if (m_player->GetIsMenu())
	{
		GetMousePoint(&m_mouseX, &m_mouseY);
		SelectEatFood();
	}

	if (m_inventory->GetEatFoodFlag() && !m_isSelect)
	{
		if (m_drawPosNum >= m_inventory->GetEatFoodPosNum())
		{
			ShiftDrawPos();
		}

		m_inventory->AddShiftIconCount();
	}
}

void Food::Draw()
{
	if (m_player->GetIsMenu())
	{
		m_iconUi.Draw(m_iconPos);
	}
}

void Food::SelectEatFood()
{
	//別のアイテムが選択されたときこのアイテムを選択されていない状態にする
	if (InventoryPos.x + (InventorySize.x / 2) >= m_mouseX &&
		InventoryPos.x - (InventorySize.x / 2) <= m_mouseX)
	{
		if (m_iconPos.position.y + (IconSize.y / 2) >= m_mouseY &&
			m_iconPos.position.y - (IconSize.y / 2) <= m_mouseY)
		{
			if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_1) && m_isSelect)
			{
				m_isSelect = false;
			}
		}
	}

	//アイテム選択
	if (m_iconPos.position.x + (IconSize.x / 2) >= m_mouseX &&
			m_iconPos.position.x - (IconSize.x / 2) <= m_mouseX)
	{
		if (m_iconPos.position.y + (IconSize.y / 2) >= m_mouseY &&
				m_iconPos.position.y - (IconSize.y / 2) <= m_mouseY)
		{
			if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_1) && !m_isSelect)
			{
				m_isSelect = true;
			}
		}
	}
}