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
	m_drawStageView = new DrawStageView("colloder_stage_view.mv1");
	uiLayer->AddChild(m_drawStageView);

	// �X�e�[�W�̓����蔻����쐬
	m_collisionStage = new CollisionStage("Resource/colloder_stage.mv1", "Resource/colloder_stage_wall.mv1", Vector3(0, 0, 0));
	uiLayer->AddChild(m_collisionStage);

	m_homeLight = new HomeLight();
	uiLayer->AddChild(m_homeLight);

	//�H�ו��̏���CSV����擾
	m_loadFoodData = new LoadFoodData();
	uiLayer->AddChild(m_loadFoodData);

	// �v���C���[
	m_loadPlayer = new LoadPlayer(m_collisionStage,Vector3(-500, 0, -500));
	actorLayer->AddChild(m_loadPlayer);
	// �J����
	m_cam = new Camera(m_loadPlayer, m_collisionStage);
	actorLayer->AddChild(m_cam);
	
	//���j���[���
	m_menu = new Menu(m_loadPlayer);
	uiLayer->AddChild(m_menu);

	//���E�̎���
	m_worldTime = new WorldTime(m_loadPlayer);

	//���z
	m_sunLight = new SunLight(m_worldTime);
	uiLayer->AddChild(m_sunLight);

	//�x�b�h
	m_bed = new Bed(m_loadPlayer, m_worldTime);
	uiLayer->AddChild(m_bed);

	//�X�L���`�F�b�NUi
	m_skillCheck = new SkillCheck(m_loadPlayer);

	//�C���x���g��
	m_inventory = new Inventory(m_loadPlayer,m_loadFoodData,m_skillCheck);

	//�؍H��
	m_treeFactory = new TreeFactory(m_ax, m_loadPlayer, m_inventory);
	uiLayer->AddChild(m_treeFactory);

	uiLayer->AddChild(m_skillCheck);
	uiLayer->AddChild(m_worldTime);

	//�̉�Ui
	m_uiBodyTemperature = new UiBodyTemperature(m_loadPlayer);
	uiLayer->AddChild(m_uiBodyTemperature);

	//�󕠓xUi
	m_hungerlevelUi = new HungerLevelUi(m_loadPlayer);
	uiLayer->AddChild(m_hungerlevelUi);

	//���CUi
	m_uiSleepiness = new UiSleepiness(m_loadPlayer);
	uiLayer->AddChild(m_uiSleepiness);

	//�g�F
	m_firePlace = new FirePlace(m_loadPlayer,m_inventory);
	actorLayer->AddChild(m_firePlace);
	
	//���z
	m_wallet = new Wallet(m_loadPlayer);
	//�g���[�hUI�n
	m_sellButton = new SellButton(m_loadPlayer,m_inventory);
	m_tredeUi = new TredeUi(m_loadPlayer,m_sellButton,m_wallet,m_inventory, m_loadFoodData);
	uiLayer->AddChild(m_tredeUi);

	uiLayer->AddChild(m_wallet);
	uiLayer->AddChild(m_sellButton);
	uiLayer->AddChild(m_inventory);

	//�g���[�_�[
	m_treder = new Treder(m_tredeUi);
	actorLayer->AddChild(m_treder);
	
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

	//�Q�[���N���A�V�[���֑J��
	if (m_worldTime->GetIsClear())
	{
		
	}

	if (m_loadPlayer->GetIsFinsh())
	{

	}

	if(!m_loadPlayer->GetNowTrede() && !m_loadPlayer->GetIsMenu())
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
