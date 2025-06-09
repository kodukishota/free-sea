#include "Effect.h"
#include "EffectManager.h"
#include "DxLib.h"

//�R���X�g���N�^
Effect::Effect(const char* fileName, const float effectSize, const int playInterval) :
    m_effectHandle(-1),
    m_playingEffectHandle(-1),
    m_effectPlayInterval(playInterval),
    m_playCount(0)
{
    //�G�t�F�N�g�̓o�^
    m_effectHandle = EffectManager::GetInstance()->Load(fileName, effectSize);
}

//�f�X�g���N�^
Effect::~Effect()
{
    //�G�t�F�N�g�̊J��
    DeleteEffekseerEffect(m_effectHandle);
}

//�X�V
void Effect::Update(const Vector3& position)
{
    //�Đ����̃G�t�F�N�g���ړ�����B
    SetPosPlayingEffekseer3DEffect(m_playingEffectHandle, position.x, position.y, position.z);
}

//�G�t�F�N�g���Đ�����
void Effect::Play(bool loop)
{
    //����I�ɃG�t�F�N�g���Đ�����
    if (!(m_playCount % m_effectPlayInterval))
    {
        m_playingEffectHandle = PlayEffekseer3DEffect(m_effectHandle);
    }

    //�Đ��J�E���g��i�߂�
    if (loop) m_playCount++;
    else m_playCount = m_effectPlayInterval;
}

//�Đ����̃G�t�F�N�g���~����
void Effect::Stop()
{
	//�Đ����̃G�t�F�N�g���~����
	StopEffekseer3DEffect(m_playingEffectHandle);
    m_effectHandle = -1;
	m_playingEffectHandle = -1;
}