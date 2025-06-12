#pragma once
#include "Actor3D.h"

class Seeding : public Actor3D
{
private:
	static constexpr float GrowthTime = 120;

	float m_growthTime;	//�c�؂��؂ɐ������鎞��

protected:
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Seeding();
};