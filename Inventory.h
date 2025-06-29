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
class Ax;
class SkillCheck;

class Inventory : public Node
{
private:
	//���ݎ����Ă��镀�������\������UI�̏����ʒu
	static constexpr Vector2 TakeItemUiPos = Vector2(60,890);		
	static constexpr Vector2 AxInventoryUiPos = Vector2(60, 890);		//���̘g�̈ʒu
	static constexpr Vector2 AxMenuInventoryUiPos = Vector2(150, 300);	//���̘g�̈ʒu���j���[��
	static constexpr Vector2 FoodInventoryUiPos = Vector2(150, 800);	//�H�ו����̘g�̈ʒu
	static constexpr Vector2 WoodIconPos = Vector2(320, 850);
	static constexpr Vector2 MenuWoodIconPos = Vector2(125, 370);
	static constexpr Vector2 SeedlingIconPos = Vector2(500, 850);
	static constexpr Vector2 MenuSeedlingIconPos = Vector2(125, 450);
	static constexpr Vector2 WoodMenuIconPos = Vector2(160, 400);
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��

	static constexpr int MaxHaveItem = 10;

	static constexpr int MaxHaveAx = 3;
	static constexpr int MaxhaveFood = 10;

	static constexpr int SquareSize = 100;

	int m_maxHaveItem;

	int m_haveFoodCount;	//���ׂ��̂������Ă鐔
	int m_haveWoodCount;	//�؂������Ă��鐔
	int m_haveSeedlingCount;	//�c�؂������Ă��鐔
	int m_haveAxCount;		//���������Ă��鐔
	
	int m_takeFood;	//�����̃A�C�e���������Ă��邩
	int m_takeAx;	//�����Ԗڂ̕��������Ă��邩

	bool m_canGetItem;			//�A�C�e�����E���邩
	bool m_gettingItem;			//�A�C�e�����E������
	bool m_dropItemCompletion;

	bool m_isCutTree;

	bool m_selectFood;		//�A�C�e����I�����Ă��邩
	int m_eatFoodPosNum;	//�H�ׂ��H�ו��̕`�悳��Ă��鏇�Ԃ̔ԍ�
	bool m_eatFoodFlag;		//�H�ו���H�ׂ���

	int m_shiftIconCount;

	int m_itemNum;		//�A�C�e���̔ԍ��i�[�p

	bool m_breakAx;

	int m_seInventory;	//�T�E���h
	int m_seEat;

	int m_fontTextureId;	// �����t�H���g
	Transform m_haveWeightTransform;	// �p��

	//�A�C�e���i�[�p
	std::vector<Food*> m_foodList;
	std::vector<Ax*> m_axList;

	Sprite m_axInventoryUi;
	Sprite m_foodInventoryUi;
	Sprite m_takeItemUi;
	Transform m_axInventoryPos;		// �p��
	Transform m_foodInventoryPos;	// �p��
	Transform m_takeItemTransform;	// �p��

	int m_woodIcon;
	int m_seedlingIcon;

	Vector2 m_woodIconPos;
	Vector2 m_seedlingIconPos;

	LoadFoodData* m_loadFoodData;
	LoadPlayer* m_player;
	EatButton* m_eatButton;
	Food* m_food;
	Ax* m_ax;
	SkillCheck* m_skillCheck;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Inventory(LoadPlayer* player,LoadFoodData* loadFoodData,SkillCheck* skillCheck);

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
 
	std::vector<Ax*> GetAxList()
	{
		return m_axList;
	}

	int GetTakeAx()
	{
		return m_takeAx;
	}

	int GetHaveSeedlingCount()
	{
		return m_haveSeedlingCount;
	}

	//�c�؂�A�����Ƃ��ɕc�؂̏����������炷
	void UseSeedling()
	{
		m_haveSeedlingCount--;
	}

	//�c�؂��w�������Ƃ�
	void BuySeedling()
	{
		m_haveSeedlingCount++;
	}

	bool GetBreakAx()
	{
		return m_breakAx;
	}

	bool GetIsCutTree()
	{
		return m_isCutTree;
	}
 
	//�������H�ו������j���[�ŕ\��������
	void BuyFood(int foodId);

	//���𔃂������̃A�C�R����\��������
	void BuyAx(int axId);

	//�I�������H�ו���H�ׂ�
	void EatFood();

	//�}�E�X�z�C�[���ŕ���I������
	void SelectAx();

	void BreakAx();
};