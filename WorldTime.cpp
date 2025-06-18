#include "WorldTime.h"
#include "Time.h"
#include "ImageLoader.h"
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
	m_worldTimeMinutes += Time::GetInstance()->GetDeltaTime();

	m_worldTimeHour = m_worldTimeMinutes / 60;

	m_worldDays = m_worldTimeHour / 24;
}

void WorldTime::Draw()
{
	//現在の時刻(分)の数を描画
	Vector2 nowTimeMinutesUiPos = Vector2(1300, 100);
	nowTimeMinutesUiPos.y += FontMargin;
	int nowTimeMinutes = m_worldTimeMinutes;
	int nowTimeMinutesDigit = 1;
	do
	{
		int value = nowTimeMinutes % 10;	// 1の位の値を取り出す

		if (m_worldTimeMinutes <= 10)
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
		nowTimeMinutesDigit++;		// 次の桁へ
	} while (nowTimeMinutes > 0);

	//現在の時刻(時)の数を描画
	Vector2 nowTimeHourUiPos = Vector2(1250, 100);
	nowTimeHourUiPos.y += FontMargin;
	int nowTimeHour = m_worldTimeHour;
	int nowTimeHourDigit = 1;
	do
	{
		int value = nowTimeHour % 10;	// 1の位の値を取り出す

		if (m_worldTimeHour <= 10)
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
		nowTimeHourDigit++;		// 次の桁へ
	} while (nowTimeHour > 0);
}