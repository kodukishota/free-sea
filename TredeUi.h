#pragma once
#include "Node.h"
#include "Sprite.h"
#include <vector>

class LoadPlayer;
class SellButton;
class Wallet;
class Inventory;
class SelectProduct;
class BuyButton;

struct ProductData
{
	char m_itemName[256];
	char m_iconName[256];
	char m_flavorText[256];
	int m_needMoney;
};

class TredeUi : public Node
{
public:
	enum class TredeItem
	{
		test1,
		test2,
		test3,

		Length
	};
private:

	static constexpr Vector2 UiPos = Vector2(720, 430);
	static constexpr Vector2 ProductUiPos = Vector2(720, 200);

	Sprite m_sprite;
	Transform m_transform;

	Sprite m_productUi;
	Transform m_productTransform;

	bool m_nowTredeFlag;

	int m_seSell;

	bool m_selectFlag;
	int m_selectProductNum;

	LoadPlayer* m_player;
	SellButton* m_sellButton;
	Wallet* m_wallet;
	Inventory* m_inventory;
	SelectProduct* m_selectProduct[static_cast<int>(TredeItem::Length)];
	BuyButton* m_buyButton;

	ProductData m_productData[static_cast<int>(TredeItem::Length)];

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	TredeUi(LoadPlayer* player,	SellButton* sellButton,	Wallet* wallet,	Inventory* inventory);

	void LoadBuyItem();

	void ProductDisplay();

	void BuyProduct();

	int GetSelectItemMoney()
	{
		return m_productData[m_selectProductNum].m_needMoney;
	}

	bool GetSelectFlag()
	{
		return m_selectFlag;
	}

	char* GetIconName()
	{
		return m_productData[m_selectProductNum].m_iconName;
	}
};