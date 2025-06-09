#include "Effect.h"
#include "EffectManager.h"
#include "DxLib.h"

//コンストラクタ
Effect::Effect(const char* fileName, const float effectSize, const int playInterval) :
    m_effectHandle(-1),
    m_playingEffectHandle(-1),
    m_effectPlayInterval(playInterval),
    m_playCount(0)
{
    //エフェクトの登録
    m_effectHandle = EffectManager::GetInstance()->Load(fileName, effectSize);
}

//デストラクタ
Effect::~Effect()
{
    //エフェクトの開放
    DeleteEffekseerEffect(m_effectHandle);
}

//更新
void Effect::Update(const Vector3& position)
{
    //再生中のエフェクトを移動する。
    SetPosPlayingEffekseer3DEffect(m_playingEffectHandle, position.x, position.y, position.z);
}

//エフェクトを再生する
void Effect::Play(bool loop)
{
    //定期的にエフェクトを再生する
    if (!(m_playCount % m_effectPlayInterval))
    {
        m_playingEffectHandle = PlayEffekseer3DEffect(m_effectHandle);
    }

    //再生カウントを進める
    if (loop) m_playCount++;
    else m_playCount = m_effectPlayInterval;
}

//再生中のエフェクトを停止する
void Effect::Stop()
{
	//再生中のエフェクトを停止する
	StopEffekseer3DEffect(m_playingEffectHandle);
    m_effectHandle = -1;
	m_playingEffectHandle = -1;
}