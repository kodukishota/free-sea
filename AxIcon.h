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

	static constexpr int GaugeLeft = 20;	// �Q�[�W�̍��[�̍��W
	static constexpr int GaugeRight = 100;	// �Q�[�W�̉E�[�̍��W
	static constexpr int GaugeY = 920;		// �Q�[�W��Y���W
	static constexpr int GaugeHeight = 10;	// �Q�[�W�̍���
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// �Q�[�W�̕�

	int m_rightX;	// �Q�[�W�̉E��X���W

	float m_Durability;	// �ϋv�͂̎c��̔䗦

	Ax* m_ax;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	AxIcon(Ax* ax);
};
