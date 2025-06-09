#pragma once
#include "Node.h"
#include "Vector3.h"

class Effect : Node
{
private:
	static constexpr float EffectMoveSpeed = 0.2f;	//エフェクトが移動する速度

	int m_effectPlayInterval;	//エフェクトを再生する周期
	int m_effectHandle;			//エフェクトのリソース用
	int m_playingEffectHandle;	//再生中のエフェクトハンドル
	int m_playCount;

public:
	//コンストラクタ
	Effect(const char* filePath, const float effectSize, const int playInterval = 150);

	// デストラクタ
	~Effect();						

	void Update(const Vector3& position = Vector3());		// 更新
	void Play(bool loop = true);							// 再生
	void Stop();											// 再生中のエフェクトを停止する
};