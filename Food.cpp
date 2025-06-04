#include "Food.h"
#include "TredeUi.h"
#include "DxLib.h"
#include <cmath>

Food::Food(int foodNum,TredeUi* tredeUi) :
	m_canGetItem(false),
	m_playerToDistance(0),
	m_iconName(),
	m_flavorText(),
	m_tredeUi(tredeUi)
{
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

	m_iconUi.Register(m_tredeUi->GetIconName());
}

void Food::Load()
{
	m_iconUi.Load();
}

void Food::Release()
{
	m_iconUi.Release();
}

void Food::Update()
{
	m_iconUi.Update();
}

void Food::Draw()
{
	m_iconUi.Draw(m_iconPos);
}