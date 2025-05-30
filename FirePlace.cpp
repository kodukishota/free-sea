#include "FirePlace.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "Stump.h"

FirePlace::FirePlace(LoadPlayer* player) : Actor3D("FirePlace"),
m_model(MV1LoadModel("Resource/home/firePlace.mv1")),
m_player(player)
{
	//拾える範囲の設定
	m_collider = new BoxCollider3D(CanWarmthRange , WarmthRangeOffset);

	m_transform.position = FirePlacePos;

	MV1SetPosition(m_model, m_transform.position);
}

void FirePlace::Load()
{
	Actor3D::Load();
}

void FirePlace::Release()
{
	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);

	Actor3D::Release();
}

void FirePlace::Update()
{
	Actor3D::Update();
}

void FirePlace::Draw()
{
	MV1DrawModel(m_model);

	Actor3D::Draw();
}