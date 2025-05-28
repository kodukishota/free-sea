#include "Tree.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"

Tree::Tree(Ax* ax, LoadPlayer* player) : Actor3D("Tree"),
	m_helth(FristHelth),
	m_model(MV1LoadModel("Resource/Tree/tree.mv1")),
	m_ax(ax),
	m_player(player)
{
	//拾える範囲の設定
	m_collider = new BoxCollider3D(CanCutRange);

	m_transform.position = OffSet;

	MV1SetPosition(m_model,m_transform.position);

}

void Tree::Load()
{
	Actor3D::Load();
}

void Tree::Release()
{
	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);

	Actor3D::Release();
}

void Tree::Update()
{
	Actor3D::Update();

	if (m_ax->GetIsCutTree())
	{
		m_helth -= m_ax->GetCutDamage();

		m_ax->OffIsCutTree();
	}

	if (m_helth <= 0)
	{
		m_player->FellDownTree();
	}
}

void Tree::Draw()
{
	MV1DrawModel(m_model);

#ifdef _DEBUG
	DrawFormatString(0, 400, GetColor(255, 255, 255),
		"tree Vector3(%.0f, %.0f, %.0f)",
		m_transform.position.x, m_transform.position.y, m_transform.position.z
	);

	DrawFormatString(0, 450, GetColor(255, 255, 255),
		"tree helth %d",
		m_helth
	);

#endif // _DEBUG


	Actor3D::Draw();
}