#include "SceneGame.h"
#include "SceneTitle.h"
#include "Screen.h"
#include "Input.h"
#include "Node.h"
#include "Actor.h"
#include "HitBox.h"
#include "Time.h"
#include "Fade.h"
#include "ImageLoader.h"
#include "LoadPlayer.h"
#include "Collision3D.h"
#include "Inventory.h"
#include "CollisionStage.h"
#include "NavMesh.h"
#include "DrawStageView.h"
#include "ScreenFilter.h"
#include "Camera.h"
#include "Ax.h"
#include "AxIcon.h"
#include "Tree.h"
#include "DxLib.h"

#include"Stump.h"

#include "Item.h"


// 初期化
void SceneGame::Initialize()
{
	// ルート
	m_rootNode = new Node();

	// アクターレイヤー
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	// UIレイヤー
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);
	
	// ステージの見た目を描画
	//m_drawStageView = new DrawStageView("stage_view_2.mv1");
	//uiLayer->AddChild(m_drawStageView);

	// ステージの当たり判定を作成
	m_collisionStage = new CollisionStage("Resource/nav_test_stage.mv1", "Resource/stage_wall.mv1", Vector3(0, 0, 0));
	uiLayer->AddChild(m_collisionStage);

	//インベントリ
	m_inventory = new Inventory();
	uiLayer->AddChild(m_inventory);
	
	// プレイヤー
	m_loadPlayer = new LoadPlayer(m_collisionStage,m_inventory,Vector3(300, 0, 0));
	actorLayer->AddChild(m_loadPlayer);
	
	// カメラ
	m_cam = new Camera(m_loadPlayer, m_collisionStage);
	actorLayer->AddChild(m_cam);

	//斧
	m_ax = new Ax(m_loadPlayer,m_cam);
	actorLayer->AddChild(m_ax);

	m_axIcon = new AxIcon(m_ax);
	uiLayer->AddChild(m_axIcon);

	//木
	m_tree = new Tree(m_ax,m_loadPlayer);
	actorLayer->AddChild(m_tree);


	/*
#ifdef _DEBUG
	//アイテム
	m_item = new Item(1, Vector3(300, 0, 0),m_inventory,m_loadPlayer);
	actorLayer->AddChild(m_item);//アイテム
	m_item = new Item(0, Vector3(300, 0, 0),m_inventory, m_loadPlayer);
	actorLayer->AddChild(m_item);

	m_item = new Item(3, Vector3(300, 0, 0), m_inventory, m_loadPlayer);
	actorLayer->AddChild(m_item);
	m_item = new Item(4, Vector3(300, 0, 200), m_inventory, m_loadPlayer);
	actorLayer->AddChild(m_item);
	m_item = new Item(0, Vector3(300, 0, 500), m_inventory, m_loadPlayer);
	actorLayer->AddChild(m_item);
	m_item = new Item(2, Vector3(500, 0, 200), m_inventory, m_loadPlayer);
	actorLayer->AddChild(m_item);
	m_item = new Item(6, Vector3(500, 0, 500), m_inventory, m_loadPlayer);
	actorLayer->AddChild(m_item);
	m_item = new Item(7, Vector3(400, 0, 500), m_inventory, m_loadPlayer);
	actorLayer->AddChild(m_item);

#endif // _DEBUG
	*/
	
	// スクリーンに掛けるフィルター
	m_screenFilter = new ScreenFilter(m_loadPlayer);
	uiLayer->AddChild(m_screenFilter);

	// マウスカーソルを非表示にする
	SetMouseDispFlag(false);
}

// 終了
void SceneGame::Finalize()
{
	// ノードの削除
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

// 更新
SceneBase* SceneGame::Update()
{
	// ノードの更新
	m_rootNode->TreeUpdate();
	
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_T))
	{
		return new SceneTitle();
	}

	return this;
}

// 描画
void SceneGame::Draw()
{
	// ノードの描画
	m_rootNode->TreeDraw();
}
