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
#include "SkillCheak.h"
#include "Ax.h"
#include "AxIcon.h"
#include "Tree.h"
#include "UiBodyTemperature.h"
#include "UiSleepiness.h"
#include "HungerLevelUi.h"
#include "FirePlace.h"
#include "Treder.h"
#include "TredeUi.h"
#include "SellButton.h"
#include "Wallet.h"
#include "Menu.h"
#include "LoadFoodData.h"
#include "TreeFactory.h"
#include "WorldTime.h"
#include "Bed.h"
#include "HomeLight.h"
#include "SunLight.h"
#include "DxLib.h"

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
	m_drawStageView = new DrawStageView("colloder_stage_view.mv1");
	uiLayer->AddChild(m_drawStageView);

	// ステージの当たり判定を作成
	m_collisionStage = new CollisionStage("Resource/colloder_stage.mv1", "Resource/colloder_stage_wall.mv1", Vector3(0, 0, 0));
	uiLayer->AddChild(m_collisionStage);

	m_homeLight = new HomeLight();
	uiLayer->AddChild(m_homeLight);

	//食べ物の情報をCSVから取得
	m_loadFoodData = new LoadFoodData();
	uiLayer->AddChild(m_loadFoodData);

	// プレイヤー
	m_loadPlayer = new LoadPlayer(m_collisionStage,Vector3(-500, 0, -500));
	actorLayer->AddChild(m_loadPlayer);
	// カメラ
	m_cam = new Camera(m_loadPlayer, m_collisionStage);
	actorLayer->AddChild(m_cam);
	
	//メニュー画面
	m_menu = new Menu(m_loadPlayer);
	uiLayer->AddChild(m_menu);

	//世界の時間
	m_worldTime = new WorldTime(m_loadPlayer);

	//太陽
	m_sunLight = new SunLight(m_worldTime);
	uiLayer->AddChild(m_sunLight);

	//ベッド
	m_bed = new Bed(m_loadPlayer, m_worldTime);
	uiLayer->AddChild(m_bed);

	//スキルチェックUi
	m_skillCheck = new SkillCheck(m_loadPlayer);

	//インベントリ
	m_inventory = new Inventory(m_loadPlayer,m_loadFoodData,m_skillCheck);

	//木工場
	m_treeFactory = new TreeFactory(m_ax, m_loadPlayer, m_inventory);
	uiLayer->AddChild(m_treeFactory);

	uiLayer->AddChild(m_skillCheck);
	uiLayer->AddChild(m_worldTime);

	//体温Ui
	m_uiBodyTemperature = new UiBodyTemperature(m_loadPlayer);
	uiLayer->AddChild(m_uiBodyTemperature);

	//空腹度Ui
	m_hungerlevelUi = new HungerLevelUi(m_loadPlayer);
	uiLayer->AddChild(m_hungerlevelUi);

	//眠気Ui
	m_uiSleepiness = new UiSleepiness(m_loadPlayer);
	uiLayer->AddChild(m_uiSleepiness);

	//暖炉
	m_firePlace = new FirePlace(m_loadPlayer,m_inventory);
	actorLayer->AddChild(m_firePlace);
	
	//財布
	m_wallet = new Wallet(m_loadPlayer);
	//トレードUI系
	m_sellButton = new SellButton(m_loadPlayer,m_inventory);
	m_tredeUi = new TredeUi(m_loadPlayer,m_sellButton,m_wallet,m_inventory, m_loadFoodData);
	uiLayer->AddChild(m_tredeUi);

	uiLayer->AddChild(m_wallet);
	uiLayer->AddChild(m_sellButton);
	uiLayer->AddChild(m_inventory);

	//トレーダー
	m_treder = new Treder(m_tredeUi);
	actorLayer->AddChild(m_treder);
	
	// スクリーンに掛けるフィルター
	m_screenFilter = new ScreenFilter(m_loadPlayer);
	uiLayer->AddChild(m_screenFilter);
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

	//ゲームクリアシーンへ遷移
	if (m_worldTime->GetIsClear())
	{
		
	}

	if (m_loadPlayer->GetIsFinsh())
	{

	}

	if(!m_loadPlayer->GetNowTrede() && !m_loadPlayer->GetIsMenu())
	{
		// マウスカーソルを非表示にする
		SetMouseDispFlag(false);
	}
	else
	{
		// マウスカーソルを非表示にする
		SetMouseDispFlag(true);
	}

	return this;
}

// 描画
void SceneGame::Draw()
{
	// ノードの描画
	m_rootNode->TreeDraw();
}
