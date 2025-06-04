#include "Food.h"
#include "TredeUi.h"
#include "DxLib.h"
#include <cmath>

Food::Food(int foodNum,TredeUi* tredeUi) :
	m_canGetItem(false),
	m_playerToDistance(0),
	m_iconName(),
	m_flavorText(),
	m_tredeUi(tredeUi)
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

	m_iconUi.Register(m_tredeUi->GetIconName());
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
}

void Food::Draw()
{
	m_iconUi.Draw(m_iconPos);
}