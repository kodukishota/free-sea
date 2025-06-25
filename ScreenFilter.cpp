#include"ScreenFilter.h"
#include"LoadPlayer.h"
#include"Screen.h"
#include"DxLib.h"

const char* ScreenFilter::FilterTexture[FilterNum]
{
	"gray.png",
	"red.png"
};

ScreenFilter::ScreenFilter(LoadPlayer* player) :
	m_player(player)
{
	//��ꂽ��
	m_grayImg.Register(FilterTexture[0]);
	//���܂��Ă��鎞
	m_redImg.Register(FilterTexture[1]);

	m_transform.position = Screen::Center;
}

void ScreenFilter::Load()
{
	m_grayImg.Load();
	m_redImg.Load();
}

void ScreenFilter::Release()
{
	m_grayImg.Release();
	m_redImg.Release();
}

void ScreenFilter::Update()
{
	m_grayImg.Update();
	m_redImg.Update();
}

void ScreenFilter::Draw()
{
	// �v���C���[�̗̑͂̊������擾
	float ratio = m_player->GetHpRatio();
	//int pal = MaxPal - static_cast<int>(MaxPal * ratio);

	// �摜�𔼓����ŕ\��
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);

	if (m_player->GetIsTired())
	{
		m_grayImg.Draw(m_transform);
	}
	m_redImg.Draw(m_transform);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
}
