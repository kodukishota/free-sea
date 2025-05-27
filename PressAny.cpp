#include "PressAny.h"
#include "Time.h"
#include "Screen.h"

// �R���X�g���N�^
PressAny::PressAny() :
	Actor(
		"PressAny",
		"press_any_button.png",
		Screen::BottomCenter - Vector2(0, Screen::Height / 4)
	),
	m_elapsedTime(0),
	m_drawFlag(true)
{
}

// �X�V
void PressAny::Update()
{
	// ��莞�Ԍo�߂�����A�`��t���O�����ւ���
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= BlinkDuration)
	{
		m_elapsedTime -= BlinkDuration;
		m_drawFlag = !m_drawFlag;
	}
}

// �`��
void PressAny::Draw()
{
	if (!m_drawFlag) return;

	// �{���̕`�揈��
	Actor::Draw();
}
