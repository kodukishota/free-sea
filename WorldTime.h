#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Sprite.h"

class LoadPlayer;

class WorldTime : public Node
{
private:
	static constexpr Vector2 FontSize = Vector2(20, 35);	// 数字1文字の幅・高さ

	static constexpr Vector2 TimerPos = Vector2(1251, 105);
	static constexpr Vector2 SpendDaysUiPos = Vector2(1050, 170);

	static constexpr int ClearDays = 15;	//生き残らなければいけない日数

	static constexpr int FontMargin = 5;					// 数字と数字の間の余白

	int m_worldDays;			//世界を過ごした日にち
	float m_worldTimeMinutes;	//世界を過ごした分
	float m_worldTimeHour;		//世界を過ごした時

	int m_timeFontId;	// 数字フォント

	int m_timerUi;
	int m_spendDaysUi;

	LoadPlayer* m_player;

protected:
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	WorldTime(LoadPlayer* player);

	//ベットで寝たら時間を飛ばす
	void SleepSpendTime()
	{
		m_worldTimeMinutes += 480;
	}

	//仮眠した時に時間を飛ばす
	void NapSpendTime()
	{
		m_worldTimeMinutes += 180;
	}

	float GetWorldTimeMinutes()
	{
		return m_worldTimeMinutes;
	}

	bool ClearSpendDays();

	bool GetIsClear()
	{
		return ClearSpendDays;
	}
};