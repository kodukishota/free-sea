#pragma once
#include "Node.h"

class LoadPlayer;

class UiBodyTemperature: public Node
{
private:
	static constexpr int GaugeLeft = 200;	// ゲージの左端の座標
	static constexpr int GaugeRight = 1080;	// ゲージの右端の座標
	static constexpr int GaugeY = 800;		// ゲージのY座標
	static constexpr int GaugeHeight = 20;	// ゲージの高さ
	static constexpr int GaugeCenter = (GaugeLeft + GaugeRight) / 2;	// ゲージの中央
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// ゲージの幅

	int m_rightX;	// ゲージの右のX座標

	LoadPlayer* m_player;

	float m_bodyTemperature;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	UiBodyTemperature(LoadPlayer* player);
};
