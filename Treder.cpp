#include "Treder.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "Stump.h"

Treder::Treder() : Actor3D("Treder"),
m_model(MV1LoadModel("Resource/Treder/treder.mv1"))
{
	//拾える範囲の設定
	m_collider = new BoxCollider3D(CanTredeRange);

	m_transform.position = TrederPos;

	MV1SetPosition(m_model, m_transform.position);
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