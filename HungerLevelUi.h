#pragma once
#include "Node.h"
#include "Sprite.h"

class LoadPlayer;

class HungerLevelUi : public Node
{
private:
	static constexpr int GaugeLeft = 20;	// ゲージの左端の座標
	static constexpr int GaugeRight = 320;	// ゲージの右端の座標
	static constexpr int GaugeY = 60;		// ゲージのY座標
	static constexpr int GaugeHeight = 20;	// ゲージの高さ
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// ゲージの幅

	static constexpr Vector2  FrameUiPos = Vector2(185, 70);

	//メニュー時
	static constexpr int InMenuGaugeLeft = 105;
	static constexpr int InMenuGaugeRight = 405;
	static constexpr int InMenuGaugeY = 130;
	static constexpr int InMenuGaugeWidth = InMenuGaugeRight - InMenuGaugeLeft;	// ゲージの幅

	static constexpr Vector2  InMenuFrameUiPos = Vector2(270, 140);

	int m_rightX;	// ゲージの右のX座標

	LoadPlayer* m_player;
	Sprite m_frameUi;
	Transform m_transform;

	float m_hungerLevel;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	HungerLevelUi(LoadPlayer* player);
};
