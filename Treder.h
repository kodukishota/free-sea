#pragma once
#include "Actor3D.h"
#include "Vector3.h"

class TredeUi;

class Treder : public Actor3D
{
private:
	static constexpr Vector3 TrederPos = Vector3(-1000, 0, -5000);
	static constexpr Vector3 CanTredeRange = Vector3(600, 300, 600);	//ŒðŠ·‚ª‚Å‚«‚é”ÍˆÍ

	int m_model;

	TredeUi* m_tredeUi;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Treder(TredeUi* tredeUi);
};