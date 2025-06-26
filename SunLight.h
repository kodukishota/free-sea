#pragma once
#include "Node.h"
#include "Vector3.h"

class WorldTime;

class SunLight : public Node
{
private:
	static constexpr Vector3 FirstSunPos = Vector3(1.0f, 0.0f, 0.0f);

	int m_light;

	float m_time;

	float PI = 3.14f;

	int m_oneDayLength = 720;

	Vector3 lightangle;

	WorldTime* m_worldTime;

	int m_shadowMapHandle;

	Vector3 hoge;

protected:
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	SunLight(WorldTime* worldTime);

	//‘¾—z‚ÌŒü‚«‚ğİ’è‚µ‘±‚¯‚é
	void SunLightUpdate();
};