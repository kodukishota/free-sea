#include "UiSleepiness.h"
#include "LoadPlayer.h"

UiSleepiness::UiSleepiness(LoadPlayer* player) :
	m_rightX(GaugeRight),
	m_player(player),
	m_sleepiness(0)
{
}

void UiSleepiness::Update()
{
	// 現在の眠気÷眠気の最大値で残体温の比率を計算
	m_sleepiness = m_player->GetSleepiness() / m_player->GetMaxSleepiness();

	if (!m_player->GetIsMenu())
	{
		m_rightX = static_cast<int>(GaugeRight - (GaugeWidth * m_sleepiness));
	}
	else
	{
		m_rightX = static_cast<int>(InMenuGaugeRight - (InMenuGaugeWidth * m_sleepiness));
	}
	/*
	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeRight;
	}
	*/
}

void UiSleepiness::Draw()
{
	if (!m_player->GetIsMenu())
	{
		// 現在の眠気ゲージ
		DrawBox(GaugeRight, GaugeY, GaugeLeft, GaugeY + GaugeHeight, GetColor(0, 0, 255), true);
		// 眠気ゲージの背景
		DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}
	else
	{
		// 現在の眠気ゲージ
		DrawBox(InMenuGaugeRight, InMenuGaugeY, InMenuGaugeLeft, InMenuGaugeY + GaugeHeight, GetColor(0, 0, 255), true);
		// 眠気ゲージの背景
		DrawBox(InMenuGaugeRight, InMenuGaugeY, m_rightX, InMenuGaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}
}
