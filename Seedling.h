#pragma once
#include "Actor3D.h"

class Seeding : public Actor3D
{
private:
	static constexpr float GrowthTime = 120;

	float m_growthTime;	//•c–Ø‚ª–Ø‚É¬’·‚·‚éŠÔ

protected:
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Seeding();
};