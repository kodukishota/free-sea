#include "Item.h"
#include "ModelLoader.h"
#include "LoadPlayer.h"
#include "Input.h"
#include "Inventory.h"
#include "BoxCollider3D.h"
#include "ActorCollision3D.h"
#include "DxLib.h"
#include <cmath>

Item::Item(int itemNum, ItemData* item, Vector3 spownPos, Inventory* inventory) :
	Actor3D("Item"),
	m_itemNumber(itemNum),
	m_itemName(),
	m_inventory(inventory),
	m_canGetItem(false),
	m_playerToDistance(0),
	m_iconName(),
	m_itemData(*item)
{
	//�|�W�V�����̐ݒ�
	m_transform.position = spownPos;

	//�E����͈͂̐ݒ�
	m_collider = new BoxCollider3D(CanGetRange, Vector3(0,0,0));

	//�A�C�e���̃��f���̃��[�h
	m_model = MV1LoadModel(item->m_modelName);

	//�|�W�V�����̐ݒ�
	MV1SetPosition(m_model, m_transform.position);
	/*
	//���O�̐ݒ�
	m_itemName = item->m_itemName;
	//���������̋��z�ݒ�
	m_sellMoney = item->m_sellMoney;
	//�A�C�e���̏d���ݒ�
	m_itemWeight = item->m_weight;
	//�A�C�R���̃e�N�X�`��ID
	m_iconName = item->m_iconName;
	//�t���[�o�[�e�L�X�g�̐ݒ�
	m_flavorText = item->m_flavorText;
	*/
}

void Item::Release()
{
	Actor3D::Release();
	//���f���̍폜
	MV1DeleteModel(m_model);
}

void Item::Update()
{
	m_canGetItem = m_inventory->CanGetItem();

	Actor3D::Update();
}

void Item::Draw()
{
	// ���f���̕`��
	MV1DrawModel(m_model);
	Actor3D::Draw();
}

void Item::OnCollision(const Actor3D* other)
{
	//�v���C���[���E����͈͂ɓ�������E����
	if (other->GetName() == "Player")
	{
		if (Input::GetInstance()->IsKeyPress(KEY_INPUT_F))
		{
			m_inventory->AddAdvanceItemList(this);
		}
	}
}

void Item::DestroyMine()
{
	ActorCollision3D::GetInstance()->Remove(this);
	Destroy();
}