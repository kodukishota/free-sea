#pragma once
#include "Node.h"

class TreeFactory : public Node
{
private:


protected:
	virtual void Update() override;

public:
	TreeFactory();
};