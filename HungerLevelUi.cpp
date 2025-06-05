#include "HungerLevelUi.h"
#include "LoadPlayer.h"

HungerLevelUi::HungerLevelUi(LoadPlayer* player) :
	m_rightX(GaugeRight),
	m_player(player),
	m_hungerLevel(0)
{
}

void HungerLevelUi::Update()
{
	// 現在の空腹度÷空腹度の最大値で残り空腹度の比率を計算
	m_hungerLevel = m_player->GetHungerLevel() / m_player->GetMaxHungerLevel();


	m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_hungerLevel));

	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeLeft;
	}

	if (m_hungerLevel != 100)
	{
		int hoge = 0;
	}

}

void HungerLevelUi::Draw()
{
	// 現在の空腹度ゲージ
	DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(255, 255, 0), true);
	// 空腹度ゲージの背景
	DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
}
