#include "Bed.h"
#include "LoadPlayer.h"
#include "WorldTime.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "ImageLoader.h"

Bed::Bed(LoadPlayer* player, WorldTime* worldTime) : Actor3D("Bed", BedPosition),
	m_model(MV1LoadModel("Resource/home/bed.mv1")),
	m_canSleep(false),
	m_player(player),
	m_worldTime(worldTime),
	m_sleepUi(0)
{
	//ベッド範囲の設定
	m_collider = new BoxCollider3D(CanSleepRnage , CanSleepRnageOffset);

	Quaternion::RotateAxisY(m_model, 160, BedPosition);
}

void Bed::Load()
{
	m_sleepUi = ImageLoader::GetInstance()->Load("sleep_ui.png");

	Actor3D::Load();
}

void Bed::Release()
{
	Actor3D::Release();
	ImageLoader::GetInstance()->Delete("sleep_ui.png");

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
		DrawGraph(static_cast<int>(SleepUiPos.x), static_cast<int>(SleepUiPos.y), m_sleepUi, true);
	}
}