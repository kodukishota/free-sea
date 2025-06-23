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
	// ���݂̋󕠓x���󕠓x�̍ő�l�Ŏc��󕠓x�̔䗦���v�Z
	m_hungerLevel = m_player->GetHungerLevel() / m_player->GetMaxHungerLevel();

	if (!m_player->GetIsMenu())
	{
		m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_hungerLevel));
	}
	else
	{
		m_rightX = static_cast<int>(InMenuGaugeLeft + (InMenuGaugeWidth * m_hungerLevel));
	}

	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeLeft;
	}
}

void HungerLevelUi::Draw()
{
	if (!m_player->GetIsMenu())
	{
		// ���݂̑̉��Q�[�W
		DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(255, 255, 0), true);
		// �̉��Q�[�W�̔w�i
		DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}
	else
	{
		// ���݂̑̉��Q�[�W
		DrawBox(InMenuGaugeLeft, InMenuGaugeY, InMenuGaugeRight, InMenuGaugeY + GaugeHeight, GetColor(255, 255, 0), true);
		// �̉��Q�[�W�̔w�i
		DrawBox(InMenuGaugeRight, InMenuGaugeY, m_rightX, InMenuGaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}
}
