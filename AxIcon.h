#pragma once
#include "Node.h"
#include"Item.h"
#include "Transform.h"
#include "Sprite.h"

class Inventory;
class Ax;
class LoadPlayer;

class AxIcon : public Node
{
private:
	static constexpr Vector2 SetPos = Vector2(60, 890);
	static constexpr Vector2 IsMenuSetPos = Vector2(150, 300);

	Sprite m_axIconUi;
	Transform m_axIconTsransform;

	//ゲーム画面時の位置
	static constexpr int GaugeLeft = 20;	// ゲージの左端の座標
	static constexpr int GaugeRight = 100;	// ゲージの右端の座標
	static constexpr int GaugeY = 920;		// ゲージのY座標
	static constexpr int GaugeHeight = 10;	// ゲージの高さ
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// ゲージの幅

	//メニュー画面時の位置
	static constexpr int InMenuGaugeLeft = 110;
	static constexpr int InMenuGaugeRight = 190;
	static constexpr int InMenuGaugeY = 330;
	static constexpr int InMenuGaugeWidth = InMenuGaugeRight - InMenuGaugeLeft;	// ゲージの幅

	int m_rightX;	// ゲージの右のX座標

	int m_haveCount;

	float m_Durability;	// 耐久力の残りの比率

	Ax* m_ax;
	LoadPlayer* m_player;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	AxIcon(Ax* ax,int haveCount,LoadPlayer* player);

	Vector2 GetDrawPos()
	{
		return m_axIconTsransform.position;
	}
};
