#pragma once
#include "Node.h"
#include "Sprite.h"

class Menu : public Node
{
private:

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	Menu();
};