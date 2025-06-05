#pragma once
#include "Node.h"

class LoadPlayer;

class HungerLevelUi : public Node
{
private:
	static constexpr int GaugeLeft = 20;	// ゲージの左端の座標
	static constexpr int GaugeRight = 320;	// ゲージの右端の座標
	static constexpr int GaugeY = 60;		// ゲージのY座標
	static constexpr int GaugeHeight = 20;	// ゲージの高さ
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// ゲージの幅

	int m_rightX;	// ゲージの右のX座標

	LoadPlayer* m_player;

	float m_hungerLevel;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	HungerLevelUi(LoadPlayer* player);
};
