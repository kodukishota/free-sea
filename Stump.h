#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"DxLib.h"

class Stump : public Actor3D
{
private:
	static constexpr Vector3 CanCutRange = Vector3(300, 150, 300);	//–Ø‚ð”°‚ê‚é”ÍˆÍ

	int m_model;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Stump(Vector3 spwonPos);
};