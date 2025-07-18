#pragma once
#include "Node.h"
#include "Sprite.h"
#include "Vector3.h"
#include <vector>

class LoadPlayer;
class SellButton;
class Wallet;
class Inventory;
class SelectProduct;
class BuyButton;
class LoadFoodData;

struct ProductData
{
	char m_itemName[256];
	char m_iconName[256];
	char m_flavorText[256];
	int m_needMoney;
	int m_productId;
	int m_productKindId;
};

class TredeUi : public Node
{
public:
	enum class TredeItem
	{
		Bread,
		Onigiri,
		Burger,
		ChillCrab,
		MeatPie,
		ChillSausage,
		FriedChicken,
		Ax,
		Seedling,

		Length
	};
private:

	static constexpr Vector2 UiPos = Vector2(720, 430);
	static constexpr Vector2 TredeUiPos = Vector2(620, 700);
	static constexpr Vector2 ProductUiPos = Vector2(520, 150);
	static constexpr float CanTredeRange = 700;

	Vector3 m_trederPos;

	Sprite m_sprite;
	Transform m_transform;

	Sprite m_productUi;
	Transform m_productTransform;
	Sprite m_selectProductUi;

	int m_sellWoodUi;

	int m_selectProductValue;	//選んでいる商品の価格

	bool m_nowTredeFlag;	//現在トレードをしているか

	int m_seSell;
	int m_seBuy;

	bool m_selectFlag;		//商品を選んでいるか
	int m_selectProductNum;	//選んでいる商品は何か

	int m_displayCount;	//商品を一列に何個並べたか

	int m_tredeUi;

	LoadPlayer* m_player;
	SellButton* m_sellButton;
	Wallet* m_wallet;
	Inventory* m_inventory;
	SelectProduct* m_selectProduct[static_cast<int>(TredeItem::Length)];
	BuyButton* m_buyButton;
	LoadFoodData* m_loadFoodData;

	ProductData m_productData[static_cast<int>(TredeItem::Length)];

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	TredeUi(
		LoadPlayer* player,
		SellButton* sellButton,
		Wallet* wallet,	
		Inventory* inventory,
		LoadFoodData* loadFoodData);

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

	int GetSelectProductValue()
	{
		return m_selectProductValue;
	}

	void SetTrederPos(Vector3 trederPos)
	{
		m_trederPos = trederPos;
	}
};