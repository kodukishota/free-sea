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
	// ���݂̖��C�����C�̍ő�l�Ŏc�̉��̔䗦���v�Z
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
		// ���݂̖��C�Q�[�W
		DrawBox(GaugeRight, GaugeY, GaugeLeft, GaugeY + GaugeHeight, GetColor(0, 0, 255), true);
		// ���C�Q�[�W�̔w�i
		DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}
	else
	{
		// ���݂̖��C�Q�[�W
		DrawBox(InMenuGaugeRight, InMenuGaugeY, InMenuGaugeLeft, InMenuGaugeY + GaugeHeight, GetColor(0, 0, 255), true);
		// ���C�Q�[�W�̔w�i
		DrawBox(InMenuGaugeRight, InMenuGaugeY, m_rightX, InMenuGaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}
}
