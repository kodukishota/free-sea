#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Sprite.h"

class LoadPlayer;

class WorldTime : public Node
{
private:
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��

	int m_worldDays;			//���E���߂��������ɂ�
	float m_worldTimeMinutes;	//���E���߂�������
	float m_worldTimeHour;		//���E���߂�������

	int m_timeFontId;	// �����t�H���g

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
};