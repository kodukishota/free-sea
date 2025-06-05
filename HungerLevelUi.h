#pragma once
#include "Node.h"

class LoadPlayer;

class HungerLevelUi : public Node
{
private:
	static constexpr int GaugeLeft = 20;	// �Q�[�W�̍��[�̍��W
	static constexpr int GaugeRight = 320;	// �Q�[�W�̉E�[�̍��W
	static constexpr int GaugeY = 60;		// �Q�[�W��Y���W
	static constexpr int GaugeHeight = 20;	// �Q�[�W�̍���
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// �Q�[�W�̕�

	int m_rightX;	// �Q�[�W�̉E��X���W

	LoadPlayer* m_player;

	float m_hungerLevel;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	HungerLevelUi(LoadPlayer* player);
};
