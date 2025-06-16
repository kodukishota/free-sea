#include "Seedling.h"
#include "Time.h"
#include "Tree.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "Inventory.h"
#include "TreeFactory.h"

Seedling::Seedling(Ax* ax,
	LoadPlayer* player,
	Inventory* inventory,
	TreeFactory* treeFactory,
	Vector3 position) : Actor3D("Seedling"),
	m_growthTime(GrowthTime),
	m_model(MV1LoadModel("Resource/Tree/seedling.mv1")),
	m_ax(ax),
	m_player(player),
	m_inventory(inventory),
	m_treeFactory(treeFactory),
	m_tree(nullptr)
{
	m_transform.position = position;

	MV1SetPosition(m_model, m_transform.position);
}

void Seedling::Load()
{
	Actor3D::Load();
}

void Seedling::Release()
{
	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);

	Actor3D::Release();
}

void Seedling::Update()
{
	Actor3D::Update();

	m_growthTime -= Time::GetInstance()->GetDeltaTime();
}

void Seedling::Draw()
{
	MV1DrawModel(m_model);

	Actor3D::Draw();
}

bool Seedling::GetIsGrow()
{
	if (m_growthTime <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}