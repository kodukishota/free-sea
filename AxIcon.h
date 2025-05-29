#pragma once
#include "Node.h"
#include"Item.h"
#include "Transform.h"
#include "Sprite.h"

class Inventory;
class Ax;

class AxIcon : public Node
{
private:
	static constexpr Vector2 SetPos = Vector2(60, 890);

	Sprite m_axIconUi;
	Transform m_axIconTsransform;

	static constexpr int GaugeLeft = 20;	// ゲージの左端の座標
	static constexpr int GaugeRight = 100;	// ゲージの右端の座標
	static constexpr int GaugeY = 920;		// ゲージのY座標
	static constexpr int GaugeHeight = 10;	// ゲージの高さ
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// ゲージの幅

	int m_rightX;	// ゲージの右のX座標

	float m_Durability;	// 耐久力の残りの比率

	Ax* m_ax;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	AxIcon(Ax* ax);
};
