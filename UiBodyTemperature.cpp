#include "UiBodyTemperature.h"
#include "LoadPlayer.h"

UiBodyTemperature::UiBodyTemperature(LoadPlayer* player) :
	m_rightX(GaugeRight),
	m_player(player)
{
}

void UiBodyTemperature::Update()
{
	// ���݂̃X�^�~�i���X�^�~�i�̍ő�l�Ŏc�X�^�~�i�̔䗦���v�Z
	m_bodyTemperature = m_player->GetStamina() / m_player->GetMaxStamina();

	// ���E�Ŕ������̕����v�Z
	m_rightX = static_cast<int>((GaugeWidth * m_bodyTemperature) / 2);

	// �X�^�~�i�Q�[�W�̊g�k�i�����ɏk�ށj
	//m_rightX = GaugeCenter + m_halfWidth;
}

void UiBodyTemperature::Draw()
{
	// ���݂̃X�^�~�i���ő�l����Ȃ��Ƃ�
	if (m_player->GetStamina() != m_player->GetMaxStamina())
	{
		// �X�^�~�i�Q�[�W�̔w�i
		DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(100, 100, 100), true);

		// ���݂̃X�^�~�i�Q�[�W�i�����ɏk�ށj
		DrawBox(GaugeLeft, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(200, 200, 0), true);
	}
}
