#include "Ax.h"
#include "Quaternion.h"
#include "LoadPlayer.h"
#include "Camera.h"
#include "Input.h"
#include "SkillCheak.h"

Ax::Ax(LoadPlayer* player, Camera* camera, SkillCheck* skillCheck) : Actor3D("Ax"),
	m_durabilityValue(FirstDurabilityValue),
	m_attackDamage(AttackDamage),
	m_consumptionDurability(ConsumptionDurability),
	m_model(MV1LoadModel("Resource/Ax/Ax.mv1")),
	m_player(player),
	m_camera(camera),
	m_isCutTreeFlag(false),
	m_skillCheck(skillCheck),
	m_cutTreeValue(0)
{	
}

void Ax::Load()
{
	Actor3D::Load();
}

void Ax::Release()
{
	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);

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

	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_4))
	{
		m_player->DownBodyTemperature();
	}

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

	Actor3D::Draw();
}

void Ax::CutTree()
{
	if (m_skillCheck->GetIsClick())
	{
		m_attackDamage = AttackDamage;
		m_consumptionDurability = ConsumptionDurability;
		m_cutTreeValue = 1;

		//押した位置がGoodやPerfectの中で押されているか
		if (m_skillCheck->GetPrefectFlag())
		{
			m_attackDamage = m_attackDamage * 2;
			m_consumptionDurability = m_consumptionDurability * 0.5f;
			m_cutTreeValue = 1.5f;

			m_skillCheck->ResetPrefectFlag();
		}
		else if (m_skillCheck->GetGoodFlag())
		{
			m_attackDamage = m_attackDamage;
			m_consumptionDurability = m_consumptionDurability;
			m_cutTreeValue = 1;

			m_skillCheck->ResetGoodFlag();
		}
		else if(m_skillCheck->GetBadFlag())
		{
			 m_attackDamage = m_attackDamage * 0.5f;
			 m_consumptionDurability = m_consumptionDurability * 1.5f;
			 m_cutTreeValue = 0.5f;

			 m_skillCheck->ResetBadFlag();
		}

		m_durabilityValue -= m_consumptionDurability;

		m_isCutTreeFlag = true;

		m_skillCheck->ResetIsClick();
	}
}