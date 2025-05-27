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
class Ax;
class Tree;

// �Q�[���V�[��
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
	Ax* m_ax;
	Tree* m_tree;

	std::vector<Item> m_chestItem;

public:
	// �R���X�g���N�^
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
		m_ax(nullptr),
		m_tree(nullptr){};

	virtual void Initialize() override;		// ������
	virtual void Finalize() override;		// �I��
	virtual SceneBase* Update() override;	// �X�V
	virtual void Draw() override;			// �`��
};
