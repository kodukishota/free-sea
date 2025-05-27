#include "Ax.h"
#include "Quaternion.h"
#include "LoadPlayer.h"
#include "Camera.h"

Ax::Ax(LoadPlayer* player, Camera* camera) : Actor3D("Ax"),
	m_durabilityValue(FristDurabilityValue),
	m_attackDamage(AttackDamage),
	m_model(MV1LoadModel("Resource/Ax/Ax.mv1")),
	m_player(player),
	m_camera(camera)
{
	m_skillCheckUi.Register("inventory_ui1.png");
	m_skillCheckHandleUi.Register("inventory_ui1.png");
	m_skillCheckUiPos.position = SkillCheckUiPos;
	m_skillCheckHandleUiPos.position = SkillCheckUiPos;

}

void Ax::Load()
{
	Actor3D::Load();
	m_skillCheckUi.Load();
	m_skillCheckHandleUi.Load();
}

void Ax::Release()
{
	// �v���C���[�̃��f�����폜
	MV1DeleteModel(m_model);
	m_skillCheckUi.Release();
	m_skillCheckHandleUi.Release();

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

#endif // _DEBUG

	if (m_player->GetCutTree())
	{
		m_skillCheckUi.Draw(m_skillCheckUiPos);
		m_skillCheckHandleUi.Draw(m_skillCheckHandleUiPos);
	}

	Actor3D::Draw();
}

void Ax::CutTree()
{
	m_skillCheckHandleUiPos.position.x += 10;
}