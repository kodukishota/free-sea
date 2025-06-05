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
	// ���݂̋󕠓x�Q�[�W
	DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(255, 255, 0), true);
	// �󕠓x�Q�[�W�̔w�i
	DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
}
