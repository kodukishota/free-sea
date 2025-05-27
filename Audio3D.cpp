#include"Audio3D.h"
#include"Time.h"
#include "DxLib.h"

Audio3D::Audio3D(const char* audioHundle, Enemy* enemy) :
	Actor3D("Audio"),
	m_durationTime(0),
	m_enemy(enemy),
	m_isSetCoolTime(true),
	m_audioHundle(audioHundle),
	m_sound(0)
{
	m_playCoolTime = static_cast<float>(rand() % MinPlayCoolTime + RangePlayCoolTime);
}

void Audio3D::Load()
{
	// 3D������ݒ�
	SetCreate3DSoundFlag(true);
	m_sound = LoadSoundMem(m_audioHundle);
	SetCreate3DSoundFlag(false);

	// �T�E���h���͂�( ������������ )�͈͂�ݒ�
	Set3DRadiusSoundMem(SoundRange, m_sound);

	// ���̍Đ�����|�C���g��ݒ�
	//Set3DPositionSoundMem(m_enemy->GetPosition(), m_sound);

}

void Audio3D::Update()
{
	// �Đ��ʒu���X�V
	//Set3DPositionSoundMem(m_enemy->GetPosition(), m_sound);

	if (!m_isSetCoolTime)
	{
		// �Đ�����܂ł̎��Ԃ�ݒ�
		m_playCoolTime = static_cast<float>(rand() % MinPlayCoolTime + RangePlayCoolTime);
		m_isSetCoolTime = true;
	}
	else
	{
		// ���Ԃ��v��
		m_durationTime += Time::GetInstance()->GetDeltaTime();

		if (m_durationTime >= m_playCoolTime)
		{
			// �Đ����Ԃ̃N�[���^�C�����I�������Đ�
			PlaySoundMem(m_sound, DX_PLAYTYPE_BACK);
			m_durationTime = 0;
			m_isSetCoolTime = false;
		}
	}
}

void Audio3D::Release()
{
	Actor3D::Release();

	DeleteSoundMem(m_sound);
}