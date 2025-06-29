#include "Tree.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "Inventory.h"

Tree::Tree(LoadPlayer* player, Inventory* inventory,Vector3 Position) : Actor3D("Tree"),
	m_helth(FristHelth),
	m_model(MV1LoadModel("Resource/Tree/tree.mv1")),
	m_player(player),
	m_inventory(inventory),
	m_isDeth(false)
{
	//拾える範囲の設定
	m_collider = new BoxCollider3D(CanCutRange);

	m_transform.position = Position;

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

	if (!m_inventory->GetAxList().empty())
	{
		//伐られたら体力を減らしてインべントリに木をいれる
		if (m_inventory->GetAxList()[m_inventory->GetTakeAx()]->GetIsCutTree())
		{
			m_helth -= m_inventory->GetAxList()[m_inventory->GetTakeAx()]->GetCutDamage();

			int takeWoodValue = CutTreeTakeValue * m_inventory->GetAxList()[m_inventory->GetTakeAx()]->GetCutTreeMagnification();

			m_inventory->TakeCutWood(takeWoodValue);

			m_inventory->GetAxList()[m_inventory->GetTakeAx()]->OffIsCutTree();
		}
	}

	//体力がゼロになったら
	if (m_helth <= 0 && !m_isDeth)
	{
		m_helth = FristHelth;

		m_isDeth = true;
	}
}

void Tree::Draw()
{
	MV1DrawModel(m_model);

#ifdef _DEBUG
	DrawFormatString(0, 450, GetColor(255, 255, 255),
		"tree helth %d",
		m_helth
	);
#endif // _DEBUG


	Actor3D::Draw();
}