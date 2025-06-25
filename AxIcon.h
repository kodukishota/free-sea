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

	//�Q�[����ʎ��̈ʒu
	static constexpr int GaugeLeft = 20;	// �Q�[�W�̍��[�̍��W
	static constexpr int GaugeRight = 100;	// �Q�[�W�̉E�[�̍��W
	static constexpr int GaugeY = 920;		// �Q�[�W��Y���W
	static constexpr int GaugeHeight = 10;	// �Q�[�W�̍���
	static constexpr int GaugeWidth = GaugeRight - GaugeLeft;	// �Q�[�W�̕�

	//���j���[��ʎ��̈ʒu
	static constexpr int InMenuGaugeLeft = 110;
	static constexpr int InMenuGaugeRight = 190;
	static constexpr int InMenuGaugeY = 330;
	static constexpr int InMenuGaugeWidth = InMenuGaugeRight - InMenuGaugeLeft;	// �Q�[�W�̕�

	int m_rightX;	// �Q�[�W�̉E��X���W

	int m_haveCount;

	float m_Durability;	// �ϋv�͂̎c��̔䗦

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
