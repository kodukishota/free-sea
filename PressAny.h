#pragma once
#include "Actor.h"

class PressAny : public Actor
{
private:
	static constexpr float BlinkDuration = 1.0f;	// ���ł̊Ԋu

	float m_elapsedTime;
	bool m_drawFlag;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	// �R���X�g���N�^
	PressAny();
};
