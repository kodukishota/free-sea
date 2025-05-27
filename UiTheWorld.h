#pragma once
#include "Actor.h"
#include "Transform.h"
#include "Sprite.h"
#include "Vector2.h"

class LoadPlayer;

class UiTheWorld : public Actor
{
private:
	static constexpr Vector2 GridSize = Vector2(80, 80);	// �A�j���[�V�����̃T�C�Y
	static constexpr int GridNum = 30;	// �A�j���R�}��
	static constexpr Vector2 Offset = Vector2(70, 70);
	static constexpr float ChangeAngleTime = 0.8f;	// �X�L���Ďg�p�\���ɍ����v�𔽓]������̂ɂ����鎞��

	int m_glassImageId;
	Sprite m_glass_backImageId;
	LoadPlayer* m_player;
	float m_elapsedTime;
	bool m_isCoolDown;
	bool m_isStop;	// ���Ԃ���~���Ă��邩
	float m_angle;	// �Î~���`�悷��ۂ̊p�x
	int m_seStopTime;
	int m_seStopTimePlay;
	int m_seStopTimeFinish;
	int m_seCoolDownFinish;
	bool m_seStart;

	const char* AnimeName[1] =
	{
		"TheWorld"
	};

	/*const Animation AnimeData[1] =
	{
		Animation("theworld_icon.png",5, 1)
	};*/

protected:
	virtual void Load() override;	// ���\�[�X�̓ǂݍ���
	virtual void Release() override;// ���\�[�X�̔j��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

public:
	UiTheWorld(LoadPlayer* player);
};
