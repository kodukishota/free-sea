#include "WorldTime.h"
#include "Time.h"
#include "ImageLoader.h"
#include "LoadPlayer.h"
#include <DxLib.h>

WorldTime::WorldTime(LoadPlayer* player)	:
	m_worldDays(0),
	m_worldTimeHour(0),
	m_worldTimeMinutes(0),
	m_player(player),
	m_timeFontId(0)
{

	m_timeFontId = ImageLoader::GetInstance()->Load("score_font.png");
}

void WorldTime::Release()
{
	ImageLoader::GetInstance()->Delete("score_font.png");
}

void WorldTime::Update()
{
	//�����̐ݒ�i��
	m_worldTimeMinutes += Time::GetInstance()->GetDeltaTime();
	//�i��
	m_worldTimeHour = m_worldTimeMinutes / 60;
	//���ɂ��̐ݒ�
	m_worldDays = m_worldTimeHour / 24;
}

void WorldTime::Draw()
{
	if (m_player->GetIsMenu())
	{

		//���݂̎���(��)�̐���`��
		Vector2 nowTimeMinutesUiPos = Vector2(1300, 100);
		nowTimeMinutesUiPos.y += FontMargin;
		int nowTimeMinutes = static_cast<int>(m_worldTimeMinutes) % 60;
		int nowTimeMinutesDigit = 1;
		do
		{
			int value = nowTimeMinutes % 10;	// 1�̈ʂ̒l�����o��

			if (static_cast<int>(m_worldTimeMinutes) % 60 < 10)
			{
				DrawRectGraph(
					static_cast<int>(nowTimeMinutesUiPos.x - FontSize.x * 2), static_cast<int>(nowTimeMinutesUiPos.y),
					static_cast<int>(FontSize.x) * 0, 0,
					static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
					m_timeFontId,
					true
				);
			}

			DrawRectGraph(
				static_cast<int>(nowTimeMinutesUiPos.x - FontSize.x * nowTimeMinutesDigit), static_cast<int>(nowTimeMinutesUiPos.y),
				static_cast<int>(FontSize.x) * value, 0,
				static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
				m_timeFontId,
				true
			);

			nowTimeMinutes /= 10;
			nowTimeMinutesDigit++;		// ���̌���
		} while (nowTimeMinutes > 0);

		//���݂̎���(��)�̐���`��
		Vector2 nowTimeHourUiPos = Vector2(1250, 100);
		nowTimeHourUiPos.y += FontMargin;
		int nowTimeHour = static_cast<int>(m_worldTimeHour) % 24;
		int nowTimeHourDigit = 1;
		do
		{
			int value = nowTimeHour % 10;	// 1�̈ʂ̒l�����o��

			if (static_cast<int>(m_worldTimeHour) % 24 < 10)
			{
				DrawRectGraph(
					static_cast<int>(nowTimeHourUiPos.x - FontSize.x * 2), static_cast<int>(nowTimeHourUiPos.y),
					static_cast<int>(FontSize.x) * 0, 0,
					static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
					m_timeFontId,
					true
				);
			}

			DrawRectGraph(
				static_cast<int>(nowTimeHourUiPos.x - FontSize.x * nowTimeHourDigit), static_cast<int>(nowTimeHourUiPos.y),
				static_cast<int>(FontSize.x) * value, 0,
				static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
				m_timeFontId,
				true
			);

			nowTimeHour /= 10;
			nowTimeHourDigit++;		// ���̌���
		} while (nowTimeHour > 0);
	}
}