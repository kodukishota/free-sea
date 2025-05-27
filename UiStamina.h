#pragma once
#include "Node.h"

class LoadPlayer;

class UiStamina : public Node
{
private:
	static constexpr int GaugeLeft = 200;	// �Q�[�W�̍��[�̍��W
	static constexpr int GaugeRight = 1080;	// �Q�[�W�̉E�[�̍��W
	static constexpr int GaugeY = 800;		// �Q�[�W��Y���W
	static constexpr int GaugeHeight = 20;	// �Q�[�W�̍���
	static constexpr int GaugeCenter = (GaugeLeft + GaugeRight) / 2;	// �Q�[�W�̒���
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// �Q�[�W�̕�

	int m_leftX;	// �Q�[�W�̍���X���W
	int m_rightX;	// �Q�[�W�̉E��X���W

	LoadPlayer* m_player;

	float m_staminaRatio;	// �X�^�~�i�̎c��̔䗦
	int m_halfWidth;		// �X�^�~�i�Q�[�W�̔����̕�

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	UiStamina(LoadPlayer* player);
};
