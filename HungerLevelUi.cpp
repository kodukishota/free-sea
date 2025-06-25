#include "HungerLevelUi.h"
#include "LoadPlayer.h"

HungerLevelUi::HungerLevelUi(LoadPlayer* player) :
	m_rightX(GaugeRight),
	m_player(player),
	m_hungerLevel(0)
{
	m_frameUi.Register("hunger_level_frame.png");

}

void HungerLevelUi::Load()
{
	m_frameUi.Load();
}

void HungerLevelUi::Release()
{
	m_frameUi.Release();

}

void HungerLevelUi::Update()
{
	m_frameUi.Update();


	// ���݂̋󕠓x���󕠓x�̍ő�l�Ŏc��󕠓x�̔䗦���v�Z
	m_hungerLevel = m_player->GetHungerLevel() / m_player->GetMaxHungerLevel();

	if (!m_player->GetIsMenu())
	{
		m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_hungerLevel));

		m_transform.position = FrameUiPos;
	}
	else
	{
		m_rightX = static_cast<int>(InMenuGaugeLeft + (InMenuGaugeWidth * m_hungerLevel));

		m_transform.position = InMenuFrameUiPos;
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

	m_frameUi.Draw(m_transform);

}
