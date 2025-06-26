#include "HomeLight.h"

HomeLight::HomeLight() : 
	m_light(0)
{
	m_light = CreatePointLightHandle(
		LightPos,
		LightRange,
		0, 0.001f, 0
	);
}

void HomeLight::Release()
{
	// ライトハンドルの削除
	DeleteLightHandle(m_light);
}
