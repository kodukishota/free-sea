#include "Food.h"
#include "DxLib.h"
#include "LoadPlayer.h"
#include "Input.h"
#include "EatButton.h"
#include <cmath>

Food::Food(int foodNum, 
	LoadPlayer* player,
	FoodData* foodData,
	int drawPosNum,
	EatButton* eatButton) :
	m_canGetItem(false),
	m_flavorText(),
	m_foodData(*foodData),
	m_foodNumber(foodNum),
	m_player(player),
	m_foodName(),
	m_mouseX(0),
	m_mouseY(0),
	m_eatButton(eatButton),
	m_isSelect(false)
{
	/*
	//名前の設定
	m_itemName = item->m_itemName;
	//売った時の金額設定
	m_sellMoney = item->m_sellMoney;
	//アイテムの重さ設定
	m_itemWeight = item->m_weight;
	//アイコンのテクスチャID
	m_iconName = item->m_iconName;
	//フレーバーテキストの設定
	m_flavorText = item->m_flavorText;
	*/


	m_iconUi.Register(foodData->m_iconName);

	m_recoveryHungry = m_foodData.m_recoveryHungry;

	m_iconPos.position = IconPos;
	m_iconPos.position.x += IconSize.x * drawPosNum;

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

	GetMousePoint(&m_mouseX, &m_mouseY);
	
	if (m_player->GetIsMenu())
	{
		SelectEatFood();
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
	if (m_eatButton->GetCheckOnClick() && m_isSelect)
	{
		m_player->EatingFood(m_recoveryHungry);
	}

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