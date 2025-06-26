#include "SunLight.h"
#include "WorldTime.h"
#include "Time.h"
#include "Dxlib.h"

SunLight::SunLight(WorldTime* worldTime) :
	m_light(0),
	m_worldTime(worldTime),
	m_shadowMapHandle(0)
{
	//m_light = CreateDirLightHandle(FirstSunPos);
//	SetLightEnable(FALSE);
	
}

void SunLight::Release()
{
	// ���C�g�n���h���̍폜
	DeleteLightHandle(m_light);
}

void SunLight::Update()
{
	m_shadowMapHandle = MakeShadowMap(1024, 1024);

	SunLightUpdate();

	Vector3 lightDirection = Vector3(lightangle.x, lightangle.z, -lightangle.z);
	
	if (0.0f <= lightDirection.y)	//�z������ł��鎞
	{
		SetLightEnable(FALSE);		//�W�����C�g�݂̖̂�����
		//�z������ł���΂���قǈÂ��`�悷��
		float alpha = 1.0f - lightDirection.y;
		SetGlobalAmbientLight(GetColorF(alpha, alpha, alpha, 0.0f));
	}
	else	//�z���o�Ă��鎞
	{
		SetLightEnable(TRUE);
	}
	
	SetLightDirection(lightDirection);	//�W�����C�g�̕����ݒ�
	SetShadowMapLightDirection(m_shadowMapHandle,lightDirection);	//�e���o�������͕W�����C�g�Ɠ����ɂ���	

	hoge = GetLightDirection();
}

void SunLight::Draw()
{
	//�V���h�E�}�b�v�Ƀ��f����`�悷��
	ShadowMap_DrawSetup(m_shadowMapHandle);
	ShadowMap_DrawEnd();

	SetUseShadowMap(0, m_shadowMapHandle);
	SetUseShadowMap(0, -1);

#ifdef _DEBUG
	DrawFormatString(0, 600, GetColor(255, 255, 255),
		"lightangle(%.0f, %.0f, %.0f)",
		hoge.x, hoge.y, hoge.z
	);


#endif // _DEBUG
}

void SunLight::SunLightUpdate()
{
	m_time = m_worldTime->GetWorldTimeMinutes();

	float sunAngle =  PI * m_time / m_oneDayLength;

	lightangle.x = cosf(sunAngle);
	lightangle.z = sinf(sunAngle);

	if (2.0f * PI < sunAngle)	//���������߂�
	{
		m_time = 0;
	}
}