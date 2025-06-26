#pragma once
#include "Node.h"
#include "Vector3.h"

class HomeLight : public Node
{
private:
	static constexpr Vector3 LightPos = Vector3(-570, 500,-900);
	static constexpr int LightRange = 800;

	int m_light;

protected:
	void Release() override;

public:
	HomeLight();
};