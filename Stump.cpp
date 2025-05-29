#include "Stump.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"

Stump::Stump(Vector3 spwonPos) : Actor3D("Stump",spwonPos),
m_model(MV1LoadModel("Resource/Tree/stump.mv1"))
{
	//拾える範囲の設定
	m_collider = new BoxCollider3D(CanCutRange);

	m_transform.position = spwonPos;

	MV1SetPosition(m_model, m_transform.position);
}

void Stump::Load()
{
	Actor3D::Load();
}

void Stump::Release()
{
	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);

	Actor3D::Release();
}

void Stump::Update()
{
	Actor3D::Update();
}

void Stump::Draw()
{
	MV1DrawModel(m_model);

	DrawFormatString(0, 400, GetColor(255, 255, 255),
		"stump Vector3(%.0f, %.0f, %.0f)",
		m_transform.position.x, m_transform.position.y, m_transform.position.z
	);

	Actor3D::Draw();
}