#include "UiBodyTemperature.h"
#include "LoadPlayer.h"

UiBodyTemperature::UiBodyTemperature(LoadPlayer* player) :
	m_rightX(GaugeRight),
	m_player(player)
{
}

void UiBodyTemperature::Update()
{
	// 現在のスタミナ÷スタミナの最大値で残スタミナの比率を計算
	m_bodyTemperature = m_player->GetStamina() / m_player->GetMaxStamina();

	// 左右で半分ずつの幅を計算
	m_rightX = static_cast<int>((GaugeWidth * m_bodyTemperature) / 2);

	// スタミナゲージの拡縮（中央に縮む）
	//m_rightX = GaugeCenter + m_halfWidth;
}

void UiBodyTemperature::Draw()
{
	// 現在のスタミナが最大値じゃないとき
	if (m_player->GetStamina() != m_player->GetMaxStamina())
	{
		// スタミナゲージの背景
		DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(100, 100, 100), true);

		// 現在のスタミナゲージ（中央に縮む）
		DrawBox(GaugeLeft, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(200, 200, 0), true);
	}
}
