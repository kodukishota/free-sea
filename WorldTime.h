#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Sprite.h"

class LoadPlayer;

class WorldTime : public Node
{
private:
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����

	static constexpr Vector2 TimerPos = Vector2(1251, 105);
	static constexpr Vector2 SpendDaysUiPos = Vector2(1050, 170);

	static constexpr int ClearDays = 15;	//�����c��Ȃ���΂����Ȃ�����

	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��

	int m_worldDays;			//���E���߂��������ɂ�
	float m_worldTimeMinutes;	//���E���߂�������
	float m_worldTimeHour;		//���E���߂�������

	int m_timeFontId;	// �����t�H���g

	int m_timerUi;
	int m_spendDaysUi;

	LoadPlayer* m_player;

protected:
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	WorldTime(LoadPlayer* player);

	//�x�b�g�ŐQ���玞�Ԃ��΂�
	void SleepSpendTime()
	{
		m_worldTimeMinutes += 480;
	}

	//�����������Ɏ��Ԃ��΂�
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