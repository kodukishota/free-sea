#include "UiStamina.h"
#include "LoadPlayer.h"

UiStamina::UiStamina(LoadPlayer* player) :
	m_leftX(GaugeLeft),
	m_rightX(GaugeRight),
	m_player(player),
	m_staminaRatio(0),
	m_halfWidth(0)
{
}

void UiStamina::Update()
{
	// ���݂̃X�^�~�i���X�^�~�i�̍ő�l�Ŏc�X�^�~�i�̔䗦���v�Z
	m_staminaRatio = m_player->GetStamina() / m_player->GetMaxStamina();

	// ���E�Ŕ������̕����v�Z
	m_halfWidth = static_cast<int>((GaugeWidth * m_staminaRatio) / 2);

	// �X�^�~�i�Q�[�W�̊g�k�i�����ɏk�ށj
	m_leftX = GaugeCenter - m_halfWidth;
	m_rightX = GaugeCenter + m_halfWidth;
}

void UiStamina::Draw()
{
	// ���݂̃X�^�~�i���ő�l����Ȃ��Ƃ�
	if (m_player->GetStamina() != m_player->GetMaxStamina())
	{
		// �X�^�~�i�Q�[�W�̔w�i
		DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(100, 100, 100), true);

		// ���݂̃X�^�~�i�Q�[�W�i�����ɏk�ށj
		DrawBox(m_leftX, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(200, 200, 0), true);
	}
}
