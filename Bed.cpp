#include "Bed.h"
#include "LoadPlayer.h"
#include "WorldTime.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"

Bed::Bed(LoadPlayer* player, WorldTime* worldTime) : Actor3D("Bed", BedPosition),
	m_model(MV1LoadModel("Resource/home/bed.mv1")),
	m_canSleep(false),
	m_player(player),
	m_worldTime(worldTime)
{
	//ベッド範囲の設定
	m_collider = new BoxCollider3D(CanSleepRnage , CanSleepRnageOffset);

	Quaternion::RotateAxisY(m_model, 160, BedPosition);
}

void Bed::Load()
{
	Actor3D::Load();
}

void Bed::Release()
{
	Actor3D::Release();

	// プレイヤーのモデルを削除
	MV1DeleteModel(m_model);
}

void Bed::Update()
{
	if (m_player->GetIsSleep())
	{
		m_worldTime->SleepSpendTime();

		m_player->ResetIsSleep();
	}

	Actor3D::Update();
}

void Bed::Draw()
{
	MV1DrawModel(m_model);
	Actor3D::Draw();

	if (m_player->CanInteractObject(BedPosition, CanSleepRnage.x, CanSleepRnageOffset))
	{
		SetFontSize(30);

		DrawString(720, 600, "F:寝る", GetColor(255, 255, 255));
	}

}