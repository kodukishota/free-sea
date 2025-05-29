#include "Ax.h"
#include "Quaternion.h"
#include "LoadPlayer.h"
#include "Camera.h"
#include "Input.h"

Ax::Ax(LoadPlayer* player, Camera* camera) : Actor3D("Ax"),
	m_durabilityValue(FirstDurabilityValue),
	m_attackDamage(AttackDamage),
	m_consumptionDurability(ConsumptionDurability),
	m_model(MV1LoadModel("Resource/Ax/Ax.mv1")),
	m_player(player),
	m_camera(camera),
	m_isCutTreeFlag(false),
	m_turnHandleRight(true),
	m_turnHandleLeft(false),
	m_positionDecision(false)
{
	m_skillCheckUi.Register("check_bar_ui.png");
	m_skillCheckHandleUi.Register("check_handle.png");
	m_checkGoodHandleUi.Register("check_good_handle.png");
	m_checkPerfectHandleUi.Register("check_perfect_handle.png");
	m_skillCheckUiPos.position = SkillCheckUiPos;
	m_skillCheckHandleUiPos.position = SkillCheckUiPos;
}

void Ax::Load()
{
	Actor3D::Load();
	m_skillCheckUi.Load();
	m_skillCheckHandleUi.Load();
	m_checkGoodHandleUi.Load();
	m_checkPerfectHandleUi.Load();
}

void Ax::Release()
{
	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);
	m_skillCheckUi.Release();
	m_skillCheckHandleUi.Release();
	m_checkGoodHandleUi.Release();
	m_checkPerfectHandleUi.Release();

	Actor3D::Release();
}

void Ax::Update()
{
	m_transform.position = m_player->GetPosition() + OffSet;
	//m_transform.position = m_camera->CamFrontVec();

	m_transform.angle = m_camera->CamFrontVec();//+ OffSet;

	//MV1SetPosition(m_model, m_transform.position);
	Quaternion::RotateAxisY(m_model, m_transform.angle.y, m_transform.position);
	MV1SetRotationXYZ(m_model, m_transform.angle);

	if (m_player->GetCutTree())
	{
		CutTree();
	}


	m_skillCheckUi.Update();
	m_skillCheckHandleUi.Update();
	m_checkGoodHandleUi.Update();
	m_checkPerfectHandleUi.Update();
	Actor3D::Update();
}

void Ax::Draw()
{
	MV1DrawModel(m_model);

#ifdef _DEBUG
		DrawFormatString(0, 300, GetColor(255, 255, 255),
			"Ax Vector3(%.0f, %.0f, %.0f)",
			m_transform.position.x, m_transform.position.y, m_transform.position.z
		);

		DrawFormatString(0, 350, GetColor(255, 255, 255),
			"耐久%f",
			m_durabilityValue
		);

#endif // _DEBUG

	if (m_player->GetCutTree())
	{
		m_skillCheckUi.Draw(m_skillCheckUiPos);
		m_checkGoodHandleUi.Draw(m_checkGoodHandleUiPos);
		m_checkPerfectHandleUi.Draw(m_checkPerfectHandleUiPos);
		m_skillCheckHandleUi.Draw(m_skillCheckHandleUiPos);
	}

	Actor3D::Draw();
}

void Ax::CutTree()
{
	//端にハンドルが来たら折り返す
	if (SkillCheckUiPos.x + SkillCheckUiPos.x / 2 
		<= m_skillCheckHandleUiPos.position.x)
	{
		m_turnHandleLeft = true;
		m_turnHandleRight = false;
	}
	else if (SkillCheckUiPos.x - SkillCheckUiPos.x / 2 
		>= m_skillCheckHandleUiPos.position.x)
	{
		m_turnHandleLeft = false;
		m_turnHandleRight = true;
	}

	if (m_turnHandleLeft)
	{
		m_skillCheckHandleUiPos.position.x -= HandleSpeed;
	}
	else if(m_turnHandleRight)
	{
		m_skillCheckHandleUiPos.position.x += HandleSpeed;
	}

	int previousPosIndex = 0;

	//GoodやPerfectの位置をランダムで設定
	if (!m_positionDecision)
	{
		int goodHandlePosIndex = GetRand(GoodHandleUiPosIndex - 1);
		
		//前回と位置が被らないように
		if (previousPosIndex == goodHandlePosIndex)
		{
			goodHandlePosIndex = GetRand(GoodHandleUiPosIndex - 1);
		}

		//前回の位置のインデクス保存用
		previousPosIndex = goodHandlePosIndex;

		//グッドの位置設定
		m_checkGoodHandleUiPos.position = SkillCheckUiPos;
		m_checkGoodHandleUiPos.position.x = GoodHandleUiPosX[goodHandlePosIndex];
		//パーフェクトの位置設定
		m_checkPerfectHandleUiPos.position = m_checkGoodHandleUiPos.position;

		m_positionDecision = true;
	}

	if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_1))
	{
		m_attackDamage = AttackDamage;
		m_consumptionDurability = ConsumptionDurability;

		//押した位置がGoodやPerfectの中で押されているか
		if (m_checkPerfectHandleUiPos.position.x + PerfectHandleSize / 2 >= m_skillCheckHandleUiPos.position.x &&
			m_checkPerfectHandleUiPos.position.x - PerfectHandleSize / 2 <= m_skillCheckHandleUiPos.position.x)
		{
			m_attackDamage = m_attackDamage * 2;
			m_consumptionDurability = m_consumptionDurability * 0.5f;
		}
		else if (m_checkGoodHandleUiPos.position.x + GoodHandleSize / 2 >= m_skillCheckHandleUiPos.position.x &&
			m_checkGoodHandleUiPos.position.x - GoodHandleSize / 2 <= m_skillCheckHandleUiPos.position.x)
		{
			m_attackDamage = m_attackDamage;
			m_consumptionDurability = m_consumptionDurability;
		}
		else
		{
			 m_attackDamage = m_attackDamage * 0.5f;
			 m_consumptionDurability = m_consumptionDurability * 1.5f;
		}

		m_durabilityValue -= m_consumptionDurability;

		m_isCutTreeFlag = true;
		m_positionDecision = false;
	}
}