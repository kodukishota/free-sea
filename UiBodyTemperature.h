#pragma once
#include "Node.h"
#include "Sprite.h"

class LoadPlayer;

class UiBodyTemperature: public Node
{
private:
	static constexpr int GaugeLeft = 20;	// �Q�[�W�̍��[�̍��W
	static constexpr int GaugeRight = 320;	// �Q�[�W�̉E�[�̍��W
	static constexpr int GaugeY = 20;		// �Q�[�W��Y���W
	static constexpr int GaugeHeight = 20;	// �Q�[�W�̍���
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// �Q�[�W�̕�

	static constexpr Vector2  FrameUiPos = Vector2(185, 30);

	//���j���[��
	static constexpr int InMenuGaugeLeft = 105;
	static constexpr int InMenuGaugeRight = 405;
	static constexpr int InMenuGaugeY = 90;
	static constexpr int InMenuGaugeWidth = InMenuGaugeRight - InMenuGaugeLeft;	// �Q�[�W�̕�

	static constexpr Vector2  InMenuFrameUiPos = Vector2(270, 100);

	int m_rightX;	// �Q�[�W�̉E��X���W

	LoadPlayer* m_player;

	Sprite m_frameUi;
	Transform m_transform;

	float m_bodyTemperature;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	UiBodyTemperature(LoadPlayer* player);
};
