#include "FirePlace.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"
#include "Effect.h"
#include "Time.h"
#include "Inventory.h"
#include "Input.h"

FirePlace::FirePlace(LoadPlayer* player, Inventory* inventory) : Actor3D("FirePlace"),
m_model(MV1LoadModel("Resource/home/firePlace.mv1")),
m_player(player),
m_inventory(inventory),
m_effect(nullptr),
m_fireDuration(FireDuration),
m_isFire(false)
{
	//範囲の設定
	m_collider = new BoxCollider3D(CanWarmthRange , WarmthRangeOffset);

	m_transform.position = FirePlacePos;

	MV1SetPosition(m_model, m_transform.position);

	m_effect = new Effect("Resource/home/fire.efk",10,50);
}

void FirePlace::Load()
{
	Actor3D::Load();
}

void FirePlace::Release()
{
	//モデルを削除
	MV1DeleteModel(m_model);

	m_effect->~Effect();

	Actor3D::Release();
}

void FirePlace::Update()
{
	Actor3D::Update();
	
	//エフェクトの位置設定
	m_effect->Update(m_transform.position);

	m_fireDuration -= Time::GetInstance()->GetDeltaTime();
	
	if (m_fireDuration >= 0)
	{
		//エフェクトの再生
		m_effect->Play(true);
		m_isFire = true;
	}
	else
	{
		m_isFire = false;

		//木を五個いれたら火がまたつけれる
		if (m_inventory->GetHaveWoodCount() >= 5 &&
			Input::GetInstance()->IsKeyDown(KEY_INPUT_F))
		{
			m_inventory->LostHaveWood(5);
			m_fireDuration = FireDuration;
		}
	}
}

void FirePlace::Draw()
{
	MV1DrawModel(m_model);

	Actor3D::Draw();
}

void FirePlace::OnCollision(const Actor3D* other)
{
	if (other->GetName() == "Player" && m_isFire)
	{
		m_player->WarmthBodyTemperature();
	}
}