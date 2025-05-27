#pragma once
#include"Node.h"

class Animation3D : public Node
{
private:
	static constexpr float m_durationTime = 0.4f;
	static constexpr int FrameRate = 60;

	int m_model;		// ���������f��
	int m_animId;		// ���[�h�����A�j���[�V����
	int m_attachAnim;	// �A�j���[�V�������A�^�b�`���ꂽ���f��
	float m_animTotalTime;	// �A�j���[�V�����̑��Đ�����
	float m_blendStart;
	float m_blendEnd;

	float m_elapsedTime;
	float m_animTime;
	bool m_isActive;
	bool m_roopFlg;
	bool m_finishAnim;	// ���[�v���Ȃ��A�j���[�V�������I��������

	bool m_isStop;	// �A�j���[�V�������~�߂邩

protected:
	virtual void Update() override;

public:
	Animation3D(const int model, const char* anim, bool roopFlg = true);
	virtual ~Animation3D();

	// �u�����h�p
	void FadeIn();
	void FadeOut();

	// �u���ɐ؂�ւ��������t
	void ChangeOut();
	void ChangeIn();

	// ���[�v���Ȃ��A�j���[�V�����̏I���t���O
	bool FinishAnim() { return m_finishAnim; }

	// �C�ӂ̃^�C�~���O�ŃA�j���[�V�������~�߂�
	void StopAnim()
	{
		m_isStop = true;
	}

	// �A�j���[�V������i�߂�
	void StartAnim()
	{
		m_isStop = false;
	}
};