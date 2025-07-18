#pragma once
#include "SceneBase.h"
#include "Item.h"
#include"Vector3.h"
#include <vector>

class Node;
class LoadPlayer;
class Camera;
class Collision3D;
class CollisionStage;
class Inventory;
class Item;
class DrawStageView;
class Wallet;
class ScreenFilter;
class SkillCheck;
class Ax;
class Tree;
class UiBodyTemperature;
class UiSleepiness;
class HungerLevelUi;
class FirePlace;
class Treder;
class TredeUi;
class SellButton;
class Menu;
class LoadFoodData;
class TreeFactory;
class WorldTime;
class Bed;
class HomeLight;
class SunLight;

class AxIcon;

// ゲームシーン
class SceneGame : public SceneBase
{
private:
	Node* m_rootNode;
	LoadPlayer* m_loadPlayer;
	Camera* m_cam;
	Collision3D* m_collision3D;
	CollisionStage* m_collisionStage;
	Inventory* m_inventory;
	Item* m_item;
	DrawStageView* m_drawStageView;
	Wallet* m_wallet;
	ScreenFilter* m_screenFilter;
	SkillCheck* m_skillCheck;
	Ax* m_ax;
	Tree* m_tree;
	UiBodyTemperature* m_uiBodyTemperature;
	UiSleepiness* m_uiSleepiness;
	HungerLevelUi* m_hungerlevelUi;
	FirePlace* m_firePlace;
	Treder* m_treder;
	TredeUi* m_tredeUi;
	SellButton* m_sellButton;
	Menu* m_menu;
	LoadFoodData* m_loadFoodData;
	TreeFactory* m_treeFactory;
	WorldTime* m_worldTime;
	Bed* m_bed;
	HomeLight* m_homeLight;
	SunLight* m_sunLight;

	AxIcon* m_axIcon;

	std::vector<Item> m_chestItem;

public:
	// コンストラクタ
	SceneGame() :
		m_rootNode(nullptr),
		m_loadPlayer(nullptr),
		m_cam(nullptr),
		m_collision3D(nullptr),
		m_item(nullptr),
		m_inventory(nullptr),
		m_collisionStage(nullptr),
		m_drawStageView(nullptr),
		m_wallet(nullptr),
		m_screenFilter(nullptr),
		m_skillCheck(nullptr),
		m_ax(nullptr),
		m_tree(nullptr),
		m_uiBodyTemperature(nullptr),
		m_uiSleepiness(nullptr),
		m_hungerlevelUi(nullptr),
		m_firePlace(nullptr),
		m_treder(nullptr),
		m_tredeUi(nullptr),
		m_sellButton(nullptr),
		m_menu(nullptr),
		m_loadFoodData(nullptr),
		m_treeFactory(nullptr),
		m_worldTime(nullptr),
		m_bed(nullptr),
		m_homeLight(nullptr),
		m_sunLight(nullptr),
	
		m_axIcon(nullptr){};

	virtual void Initialize() override;		// 初期化
	virtual void Finalize() override;		// 終了
	virtual SceneBase* Update() override;	// 更新
	virtual void Draw() override;			// 描画
};
