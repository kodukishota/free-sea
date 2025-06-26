#include "WorldTime.h"
#include "Time.h"
#include "ImageLoader.h"
#include "LoadPlayer.h"
#include "Input.h"
#include <DxLib.h>

WorldTime::WorldTime(LoadPlayer* player)	:
	m_worldDays(0),
	m_worldTimeHour(0),
	m_worldTimeMinutes(720),
	m_player(player),
	m_timeFontId(0)
{

	m_timeFontId = ImageLoader::GetInstance()->Load("score_font.png");

	m_timerUi = ImageLoader::GetInstance()->Load("timer.png");
	m_spendDaysUi = ImageLoader::GetInstance()->Load("spend_days.png");
}

void WorldTime::Release()
{
	ImageLoader::GetInstance()->Delete("score_font.png");
	ImageLoader::GetInstance()->Delete("timer.png");
	ImageLoader::GetInstance()->Delete("spend_days.png");
}

void WorldTime::Update()
{
	//時刻の設定（分
	m_worldTimeMinutes += Time::GetInstance()->GetDeltaTime();
	//（時
	m_worldTimeHour = m_worldTimeMinutes / 60;
	//日にちの設定
	m_worldDays = m_worldTimeHour / 24;

	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_9))
	{
		m_worldTimeMinutes += 60;
	}
}

void WorldTime::Draw()
{
	if (m_player->GetIsMenu())
	{
		//現在の時刻(分)の数を描画
		Vector2 nowTimeMinutesUiPos = Vector2(1300, 100);
		nowTimeMinutesUiPos.y += FontMargin;
		int nowTimeMinutes = static_cast<int>(m_worldTimeMinutes) % 60;
		int nowTimeMinutesDigit = 1;
		do
		{
			int value = nowTimeMinutes % 10;	// 1の位の値を取り出す

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
			nowTimeMinutesDigit++;		// 次の桁へ
		} while (nowTimeMinutes > 0);

		//現在の時刻(時)の数を描画
		Vector2 nowTimeHourUiPos = Vector2(1250, 100);
		nowTimeHourUiPos.y += FontMargin;
		int nowTimeHour = (static_cast<int>(m_worldTimeHour) - 5) % 24 ;
		int nowTimeHourDigit = 1;
		do
		{
			int value = nowTimeHour % 10;	// 1の位の値を取り出す

			if ((static_cast<int>(m_worldTimeHour)-5) % 24 < 10)
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

		DrawGraph(SpendDaysUiPos.x, SpendDaysUiPos.y, m_spendDaysUi, true);

		//過ごした日数を描画
		Vector2 nowWorldDaysPos = SpendDaysUiPos + Vector2(210, 50);
		nowWorldDaysPos.y += FontMargin;
		int nowWorldDays = m_worldDays;
		int nowWorldDaysDigit = 1;
		do
		{
			int value = nowWorldDays % 10;	// 1の位の値を取り出す

			DrawRectGraph(
				static_cast<int>(nowWorldDaysPos.x - FontSize.x * nowWorldDaysDigit), static_cast<int>(nowWorldDaysPos.y),
				static_cast<int>(FontSize.x) * value, 0,
				static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
				m_timeFontId,
				true
			);

			nowWorldDays /= 10;
			nowWorldDaysDigit++;		// 次の桁へ
		} while (nowWorldDays > 0);

		DrawGraph(TimerPos.x, TimerPos.y, m_timerUi,true);
	}

}

bool WorldTime::ClearSpendDays()
{
	if (m_worldDays >= ClearDays)
	{
		return true;
	}
	else
	{
		return false;
	}
}