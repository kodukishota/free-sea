#pragma once
#include"Actor3D.h"
#include"Vector3.h"

class LoadPlayer;
class Effect;
class Inventory;

class FirePlace : public Actor3D
{
private:
	static constexpr Vector3 WarmthRangeView = Vector3(600, 300, 600);	//���ނ��Ƃ��ł���͈�
	static constexpr float WarmthRange = 800;	//���ނ��Ƃ��ł���͈�
	static constexpr Vector3 WarmthRangeOffset = Vector3(0,150,-200 );	//���ނ��Ƃ��ł���͈͂����炷

	static constexpr Vector3 FirePlacePos = Vector3(0, 0, 0);

	static constexpr float FireDuration = 45.0f;

	float m_fireDuration;	//�΂̎�������

	int m_model;

	bool m_isFire;		//�΂����Ă��邩

	Effect* m_effect;

	LoadPlayer* m_player;
	Inventory* m_inventory;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	FirePlace(LoadPlayer* player,Inventory* inventory);
};