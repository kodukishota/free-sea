#include "UiBodyTemperature.h"
#include "LoadPlayer.h"

UiBodyTemperature::UiBodyTemperature(LoadPlayer* player) :
	m_rightX(GaugeRight),
	m_player(player),
	m_bodyTemperature(0)
{
	m_frameUi.Register("body_temperature_bar.png");
}

void UiBodyTemperature::Load()
{
	m_frameUi.Load();
}

void UiBodyTemperature::Release()
{
	m_frameUi.Release();
}


void UiBodyTemperature::Update()
{
	m_frameUi.Update();

	// ���݂̑̉����̉��̍ő�l�Ŏc�̉��̔䗦���v�Z
	m_bodyTemperature = m_player->GetBodyTempature() / m_player->GetMaxBodyTempature();

	if (!m_player->GetIsMenu())
	{
		m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_bodyTemperature));

		m_transform.position = FrameUiPos;
	}
	else
	{
		m_rightX = static_cast<int>(InMenuGaugeLeft + (InMenuGaugeWidth * m_bodyTemperature));

		m_transform.position = InMenuFrameUiPos;
	}
	
	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeLeft;
	}
}

void UiBodyTemperature::Draw()
{
	if (!m_player->GetIsMenu())
	{
		// ���݂̑̉��Q�[�W
		DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(255, 100, 0), true);
		// �̉��Q�[�W�̔w�i
		DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}
	else
	{
		// ���݂̑̉��Q�[�W
		DrawBox(InMenuGaugeLeft, InMenuGaugeY, InMenuGaugeRight, InMenuGaugeY + GaugeHeight, GetColor(255, 100, 0), true);
		// �̉��Q�[�W�̔w�i
		DrawBox(InMenuGaugeRight, InMenuGaugeY, m_rightX, InMenuGaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	}

	m_frameUi.Draw(m_transform);
}
