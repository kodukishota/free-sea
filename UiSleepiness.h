#pragma once
#include "Node.h"

class LoadPlayer;

class UiSleepiness : public Node
{
private:
	static constexpr int GaugeLeft = 20;	// �Q�[�W�̍��[�̍��W
	static constexpr int GaugeRight = 320;	// �Q�[�W�̉E�[�̍��W
	static constexpr int GaugeY = 90;		// �Q�[�W��Y���W
	static constexpr int GaugeHeight = 20;	// �Q�[�W�̍���
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// �Q�[�W�̕�

	//���j���[��
	static constexpr int InMenuGaugeLeft = 105;
	static constexpr int InMenuGaugeRight = 405;
	static constexpr int InMenuGaugeY = 150;
	static constexpr int InMenuGaugeWidth = InMenuGaugeRight - InMenuGaugeLeft;	// �Q�[�W�̕�

	int m_rightX;	// �Q�[�W�̉E��X���W

	LoadPlayer* m_player;

	float m_sleepiness;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	UiSleepiness(LoadPlayer* player);
};
