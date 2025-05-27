#include "Fade.h"
#include "Time.h"
#include "Lerp.h"
#include "DxLib.h"

// �R���X�g���N�^
Fade::Fade() :
	m_phase(Phase::Idle),
	m_elapsedTime(0),
	m_duration(0),
	m_beginBright(0),
	m_endBright(0)
{
}

// �X�V
void Fade::Update(int screen)
{
	// �t�F�[�h������Ȃ���Ή������Ȃ�
	if (!IsFade()) return;

	// ���Ԍo��
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();

	// ���v���Ԃɑ΂��Ă̌o�ߎ��Ԃ�0.0�`1.0�̊����ŎZ�o����
	float t = m_elapsedTime / m_duration;

	// �o�ߎ��Ԃ����v���Ԃ𒴂��Ă�����A1.0�ɐ����ăt�F�[�h�I��
	if (t >= 1.0f)
	{
		t = 1.0f;
		m_phase = Phase::Idle;
	}

	// �P�x�̑J�ڂ���`��Ԃō��
	int bright = Lerp::Exec(m_beginBright, m_endBright, t);

	// �����Ŏ󂯎�����X�N���[���ɑ΂��āA�P�x��ݒ�
	GraphFilter(screen, DX_GRAPH_FILTER_HSB, 0, 0, 0, bright);
#ifdef _DEBUG
	DrawFormatString(5, 5, GetColor(255, 0, 0), "bright:%d", bright);
#endif // _DEBUG
}

// �t�F�[�h�C��
void Fade::StartFadeIn(float duration, Color color)
{
	m_phase = Phase::Fade;
	m_elapsedTime = 0;
	m_duration = duration;
	m_beginBright = (color == Color::Black) ? BrightBlack : BrightWhite;
	m_endBright = BrightNeutral;
}

// �t�F�[�h�A�E�g
void Fade::StartFadeOut(float duration, Color color)
{

	m_phase = Phase::Fade;
	m_elapsedTime = 0;
	m_duration = duration;
	m_beginBright = BrightNeutral;
	m_endBright = (color == Color::Black) ? BrightBlack : BrightWhite;
}
