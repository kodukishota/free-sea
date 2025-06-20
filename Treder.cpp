#include "Treder.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "TredeUi.h"

Treder::Treder(TredeUi* tredeUi) : Actor3D("Treder"),
m_model(MV1LoadModel("Resource/Treder/treder.mv1")),
m_tredeUi(tredeUi)
{
	m_collider = new BoxCollider3D(CanTredeRange);

	m_transform.position = TrederPos;
	m_transform.angle.y = 180;

	m_tredeUi->SetTrederPos(m_transform.position);

	Quaternion::RotateAxisY(m_model, 70, m_transform.position);
}

void Treder::Load()
{
	Actor3D::Load();
}

void Treder::Release()
{
	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);

	Actor3D::Release();
}

void Treder::Update()
{
	Actor3D::Update();
}

void Treder::Draw()
{
	MV1DrawModel(m_model);

	Actor3D::Draw();
}