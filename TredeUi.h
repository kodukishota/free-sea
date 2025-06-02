#pragma once
#include "Node.h"
#include "Sprite.h"
#include <vector>

class LoadPlayer;
class SellButton;
class Wallet;
class Inventory;

class TredeUi : public Node
{
private:
	static constexpr Vector2 UiPos = Vector2(720, 430);

	Sprite m_sprite;
	Transform m_transform;

	bool m_nowTredeFlag;

	int m_seSell;

	LoadPlayer* m_player;
	SellButton* m_sellButton;
	Wallet* m_wallet;
	Inventory* m_inventory;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	TredeUi(LoadPlayer* player,	SellButton* sellButton,	Wallet* wallet,	Inventory* inventory);

	void LoadBuyItem();
};