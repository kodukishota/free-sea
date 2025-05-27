#pragma once
#include "Item.h"
#include "Node.h"
#include "Sprite.h"
#include "Transform.h"
#include <list>
#include <vector>

class LoadPlayer;

class KeepChest : public Node
{
private:
	//�A�C�e���i�[�p
	std::vector<Item> m_itemList;

public:
	KeepChest() {};

	void SetItemList(Item* item)
	{
		m_itemList.push_back(*item);
	}

	std::vector<Item> TakeItMenu()
	{
		return m_itemList;
	}
};