#include "UiBodyTemperature.h"
#include "LoadPlayer.h"

UiBodyTemperature::UiBodyTemperature(LoadPlayer* player) :
	m_rightX(GaugeRight),
	m_player(player),
	m_bodyTemperature(0)
{
}

void UiBodyTemperature::Update()
{
	// Œ»Ý‚Ì‘Ì‰·€‘Ì‰·‚ÌÅ‘å’l‚ÅŽc‘Ì‰·‚Ì”ä—¦‚ðŒvŽZ
	m_bodyTemperature = m_player->GetBodyTempature() / m_player->GetMaxBodyTempature();


	m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_bodyTemperature));

	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeLeft;
	}

	if (m_bodyTemperature != 100)
	{
		int hoge = 0;
	}
}

void UiBodyTemperature::Draw()
{
	// Œ»Ý‚Ì‘Ì‰·ƒQ[ƒW
	DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(255, 100, 0), true);
	// ‘Ì‰·ƒQ[ƒW‚Ì”wŒi
	DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
}
