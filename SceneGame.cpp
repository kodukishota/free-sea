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
#include "HungerLevelUi.h"
#include "FirePlace.h"
#include "Treder.h"
#include "TredeUi.h"
#include "SellButton.h"
#include "Wallet.h"
#include "Menu.h"
#include "LoadFoodData.h"
#include "DxLib.h"

#include"Stump.h"

#include "Item.h"


// ������
void SceneGame::Initialize()
{
	// ���[�g
	m_rootNode = new Node();

	// �A�N�^�[���C���[
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	// UI���C���[
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);
	
	// �X�e�[�W�̌����ڂ�`��
	//m_drawStageView = new DrawStageView("stage_view_2.mv1");
	//uiLayer->AddChild(m_drawStageView);

	// �X�e�[�W�̓����蔻����쐬
	m_collisionStage = new CollisionStage("Resource/nav_test_stage.mv1", "Resource/stage_wall.mv1", Vector3(0, 0, 0));
	uiLayer->AddChild(m_collisionStage);

	//�H�ו��̏���CSV����擾
	m_loadFoodData = new LoadFoodData();
	uiLayer->AddChild(m_loadFoodData);

	// �v���C���[
	m_loadPlayer = new LoadPlayer(m_collisionStage,Vector3(300, 0, 0));
	actorLayer->AddChild(m_loadPlayer);
	
	m_menu = new Menu(m_loadPlayer);
	uiLayer->AddChild(m_menu);

	//�C���x���g��
	m_inventory = new Inventory(m_loadPlayer,m_loadFoodData);
	uiLayer->AddChild(m_inventory);

	// �J����
	m_cam = new Camera(m_loadPlayer, m_collisionStage);
	actorLayer->AddChild(m_cam);

	//�̉�Ui
	m_uiBodyTemperature = new UiBodyTemperature(m_loadPlayer);
	uiLayer->AddChild(m_uiBodyTemperature);

	//�󕠓xUi
	m_hungerlevelUi = new HungerLevelUi(m_loadPlayer);
	uiLayer->AddChild(m_hungerlevelUi);

	//�g�F
	m_firePlace = new FirePlace(m_loadPlayer);
	actorLayer->AddChild(m_firePlace);
	
	//�X�L���`�F�b�NUi
	m_skillCheck = new SkillCheck(m_loadPlayer);
	uiLayer->AddChild(m_skillCheck);

	//��
	m_ax = new Ax(m_loadPlayer, m_cam,m_skillCheck);
	actorLayer->AddChild(m_ax);

	m_axIcon = new AxIcon(m_ax);
	uiLayer->AddChild(m_axIcon);

	//��
	m_tree = new Tree(m_ax, m_loadPlayer,m_inventory);
	actorLayer->AddChild(m_tree);

	//�g���[�_�[
	m_treder = new Treder();
	actorLayer->AddChild(m_treder);
	
	m_wallet = new Wallet(m_loadPlayer);

	//�g���[�hUI�n
	m_sellButton = new SellButton(m_loadPlayer,m_inventory);
	m_tredeUi = new TredeUi(m_loadPlayer,m_sellButton,m_wallet,m_inventory, m_loadFoodData);
	uiLayer->AddChild(m_tredeUi);

	uiLayer->AddChild(m_wallet);
	uiLayer->AddChild(m_sellButton);

	/*
#ifdef _DEBUG
	//�A�C�e��
	m_item = new Item(1, Vector3(300, 0, 0),m_inventory,m_loadPlayer);
	actorLayer->AddChild(m_item);//�A�C�e��
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
	
	// �X�N���[���Ɋ|����t�B���^�[
	m_screenFilter = new ScreenFilter(m_loadPlayer);
	uiLayer->AddChild(m_screenFilter);
}

// �I��
void SceneGame::Finalize()
{
	// �m�[�h�̍폜
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

// �X�V
SceneBase* SceneGame::Update()
{
	// �m�[�h�̍X�V
	m_rootNode->TreeUpdate();
	
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_T))
	{
		return new SceneTitle();
	}

	if(!m_loadPlayer->GetNowTrede() && !m_loadPlayer ->GetIsMenu())
	{
		// �}�E�X�J�[�\�����\���ɂ���
		SetMouseDispFlag(false);
	}
	else
	{
		// �}�E�X�J�[�\�����\���ɂ���
		SetMouseDispFlag(true);
	}

	return this;
}

// �`��
void SceneGame::Draw()
{
	// �m�[�h�̕`��
	m_rootNode->TreeDraw();
}
