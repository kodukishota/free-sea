#include "Treder.h"
#include "Quaternion.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "Ax.h"
#include "LoadPlayer.h"

Treder::Treder() : Actor3D("Treder"),
m_model(MV1LoadModel("Resource/Treder/treder.mv1"))
{
	//�E����͈͂̐ݒ�
	m_collider = new BoxCollider3D(CanTredeRange);

	m_transform.position = TrederPos;
	m_transform.angle.y = 180;

	MV1SetPosition(m_model, m_transform.position);
	MV1SetRotationXYZ(m_model,Vector3(0,100,0));
}

void Treder::Load()
{
	Actor3D::Load();
}

void Treder::Release()
{
	// �v���C���[�̃��f�����폜
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