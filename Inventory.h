#pragma once
#include "Item.h"
#include "Food.h"
#include "Node.h"
#include "Sprite.h"
#include "Transform.h"
#include <list>
#include <vector>

class LoadFoodData;
class LoadPlayer;
class EatButton;
class Food;

class Inventory : public Node
{
private:
	static constexpr Vector2 TakeItemUiPos = Vector2(60,890);
	static constexpr Vector2 AxInventoryUiPos = Vector2(60, 890);
	static constexpr Vector2 AxMenuInventoryUiPos = Vector2(150, 300);
	static constexpr Vector2 FoodInventoryUiPos = Vector2(150, 800);
	static constexpr Vector2 WoodIconPos = Vector2(370, 890);
	static constexpr Vector2 WoodMenuIconPos = Vector2(160, 400);
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��

	static constexpr int MaxHaveItem = 10;

	static constexpr int MaxHaveAx = 3;
	static constexpr int MaxhaveFood = 10;

	static constexpr int SquareSize = 100;

	int m_maxHaveItem;

	int m_haveFoodCount;	//�A�C�e���������Ă鐔
	int m_haveWoodCount;	//�؂������Ă��鐔

	int m_takeFood;			//�����̃A�C�e���������Ă��邩

	bool m_canGetItem;			//�A�C�e�����E���邩
	bool m_gettingItem;			//�A�C�e�����E������
	bool m_dropItemCompletion;

	int m_eatFoodPosNum;	//�H�ׂ��H�ו��̕`�悳��Ă��鏇�Ԃ̔ԍ�
	bool m_eatFoodFlag;		//�H�ו���H�ׂ���

	int m_shiftIconCount;

	int m_itemNum;		//�A�C�e���̔ԍ��i�[�p

	int m_seInventory;	//�T�E���h

	int m_fontTextureId;	// �����t�H���g
	Transform m_haveWeightTransform;	// �p��

	//�A�C�e���i�[�p
	std::vector<Food*> m_foodList;
	Sprite m_axInventoryUi;
	Sprite m_foodInventoryUi;
	Sprite m_takeItemUi;
	Sprite m_woodIcon;
	Transform m_axInventoryPos;	// �p��
	Transform m_foodInventoryPos;	// �p��
	Transform m_takeItemTransform;	// �p��
	Transform m_haveWoodTransform;	// �p��

	LoadFoodData* m_loadFoodData;
	LoadPlayer* m_player;
	EatButton* m_eatButton;
	Food* m_food;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Inventory(LoadPlayer* player,LoadFoodData* loadFoodData);

	bool CanGetItem()
	{
		return m_canGetItem;
	}

	void GetDropItemCompletion()
	{
		m_dropItemCompletion = true;
	}

	int GetTakeFood()
	{
		return m_takeFood;
	}

	int GetHaveFoodCount()
	{
		return m_haveFoodCount;
	}

	void TakeCutWood(int woodValue)
	{
		m_haveWoodCount += woodValue;
	}

	int GetHaveWoodCount()
	{
		return m_haveWoodCount;
	}

	void LostHaveWood(int lostValue)
	{
		m_haveWoodCount -= lostValue;
	}

	bool GetEatFoodFlag()
	{
		return m_eatFoodFlag;
	}

	int GetEatFoodPosNum()
	{
		return m_eatFoodPosNum;
	}

	void AddShiftIconCount()
	{
		m_shiftIconCount++;
	}

	void CreateFoodIcon(int foodId);

	void EatFood();
};