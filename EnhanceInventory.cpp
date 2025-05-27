#include "EnhanceInventory.h"
#include "Chest.h"
#include "Wallet.h"

EnhanceInventory::EnhanceInventory(Chest* chest, Wallet* wallet, EnhanceType* enhanceType) :
	Actor("Enhance", "enhance_inventory.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&EnhanceInventory::OnClick, this)),
	m_chest(chest),
	m_canEnhance(false),
	m_needItemNum(NeedItemNum),
	m_useItemNum(0),
	m_needMoney(FirstNeedMoney),
	m_enhanceType(enhanceType),
	m_wallet(wallet),
	m_enhanceStep(0),
	m_enhanceTypeChoice(EnhanceType::EnhanceTypeChoice::EnhanceInventory)
{	
}

//�X�V
void EnhanceInventory::Update()
{
	//�{���̍X�V����
	Actor::Update();

	//�������Ă������ƂɕK�v�f�ނ𑝂₷
	if (m_enhanceType->GetMaxHaveInventory() >= 5)
	{
		m_enhanceStep = 1;
	}
	if (m_enhanceType->GetMaxHaveInventory() >= 7)
	{
		m_enhanceStep = 2;
	}
	if (m_enhanceType->GetMaxHaveInventory() >= 8)
	{
		m_enhanceStep = 3;
	}

	m_needMoney = NeedMoney[m_enhanceStep];

	//�{�^��
	m_button.Update(m_transform.position);
}

//�`��@
void EnhanceInventory::Draw()
{
	SetFontSize(30);
	DrawFormatString(510, 120, 
		GetColor(255, 255, 255),
		"%d$",
		NeedMoney[m_enhanceStep]);
	
	SetFontSize(20);
	DrawFormatString(260, 155,
		GetColor(255, 255, 255),
		"�C���x���g���e�ʁ�%d:�����と%d",
		m_enhanceType->GetMaxHaveInventory(),
		m_enhanceType->GetMaxHaveInventory() + m_enhanceType->AddHaveInventroy);

	//�����𖞂����ĂȂ��ꍇ�̓{�^�����É�������
	if (!CheckCondition())
	{
		//�ȍ~�A�P�x�������ĕ`�悷��
		SetDrawBright(50, 50, 50);
	}

	//�{���̕`�揈��
	Actor::Draw();

	//�P�x�̐ݒ�����ɖ߂�
	SetDrawBright(255, 255, 255);

#ifdef _DEBUG
	m_button.Draw(m_transform.position);
#endif
}

//�{�^���������ꂽ���ɌĂ΂��R�[���o�b�N�֐�
void EnhanceInventory::OnClick()
{
	if (!CheckCondition()) return;

	//�����ɕK�v�ȃA�C�e��������
	m_chest->LostItem(m_useItemNum);
	m_wallet->LostMoney(m_needMoney);

	//����
	m_enhanceType->Enhance(m_enhanceTypeChoice);
}

//�{�^�����L�����ǂ����`�F�b�N
bool EnhanceInventory::CheckCondition()
{
	//���߂��l�܂ŋ���������I��
	if (m_enhanceType->GetMaxHaveInventory() < 10)
	{
		//���������邩�������邩�̔���
		if (!m_chest->GetItemList().empty())
		{
			for (int i = 0; i <= m_chest->GetItemList().size() - 1; i++)
			{
				if (m_needItemNum != std::next(m_chest->GetItemList().begin(), i)->GetItemNum() ||
					m_needMoney >= m_wallet->HaveMoney())
				{
					m_canEnhance = false;
				}
			}

			for (int i = 0; i <= m_chest->GetItemList().size() - 1; i++)
			{
				if (m_needItemNum == std::next(m_chest->GetItemList().begin(), i)->GetItemNum() &&
					m_needMoney <= m_wallet->HaveMoney())
				{
					m_canEnhance = true;
					m_useItemNum = i;
				}
				

				if (m_enhanceType->OnInventoryButton())
				{
					m_enhanceType->InventoryButtonReset();
					m_canEnhance = false;
				}
			}

			
		}
		else
		{
			m_canEnhance = false;
		}
	}

	return m_canEnhance;
}
