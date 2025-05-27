#include "Tree.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"

Tree::Tree(Ax* ax) : Actor3D("Tree"),
m_helth(FristHelth),
m_model(MV1LoadModel("Resource/Tree/tree.mv1")),
m_ax(ax)
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
	}
}

void Tree::Draw()
{
	MV1DrawModel(m_model);

#ifdef _DEBUG
	DrawFormatString(0, 300, GetColor(255, 255, 255),
		"Ax Vector3(%.0f, %.0f, %.0f)",
		m_transform.position.x, m_transform.position.y, m_transform.position.z
	);

#endif // _DEBUG


	Actor3D::Draw();
}