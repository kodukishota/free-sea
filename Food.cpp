#include "Food.h"
#include "DxLib.h"
#include "LoadPlayer.h"
#include "Input.h"
#include <cmath>

Food::Food(int foodNum, 
	LoadPlayer* player,
	FoodData* foodData,
	int drawPosNum) :
	m_canGetItem(false),
	m_playerToDistance(0),
	m_flavorText(),
	m_foodData(*foodData),
	m_foodNumber(foodNum),
	m_player(player),
	m_foodName()
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

	m_iconPos.position = IconPos + IconSize * drawPosNum;
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

	GetMousePoint(&MouseX, &MouseY);

	if (m_iconPos.position.x + (IconSize.x / 2) >= MouseX &&
		m_iconPos.position.x - (IconSize.x / 2) <= MouseX)
	{
		if (m_iconPos.position.y + (IconSize.y / 2) >= MouseY &&
			m_iconPos.position.y - (IconSize.y / 2) <= MouseY)
		{
			if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_1))
			{
				m_player->EatingFood(m_recoveryHungry);
			}
		}
	}
	
}

void Food::Draw()
{
	if (m_player->GetIsMenu())
	{
		m_iconUi.Draw(m_iconPos);
	}
}