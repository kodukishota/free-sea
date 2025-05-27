#pragma once
#include "Node.h"
#include "Transform.h"
#include "Sprite.h"

class UiTime : public Node
{
private:
	static constexpr Vector2 TimeSize = Vector2(80, 19);	// SCORE�摜�̕��E����
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr Vector2 Offset = Vector2(-50, 25);		// ��ʉE�ォ��̍���
	static constexpr int FontMargin = 5;
	static constexpr float LimitTime = 300.0f;	// ��������

	int m_fontTextureId;	// �����t�H���g
	Transform m_transform;	// �p��
	float m_limitTime;			// ���Ԃ̒l
	bool m_isFinsh;		// ���Ԑ؂�t���O

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	UiTime();

	// ���Ԑ؂�t���O���󂯎��
	bool IsFinsh()
	{
		return m_isFinsh;
	}
};
