#include "EnhanceTheWorldTime.h"
#include "Chest.h"
#include "Wallet.h"

EnhanceTheWorldTime::EnhanceTheWorldTime(Chest* chest, Wallet* wallet, EnhanceType* enhanceType) :
	Actor("Enhance", "enhance_theWorld_time.png", Position),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&EnhanceTheWorldTime::OnClick, this)),
	m_chest(chest),
	m_canEnhance(false),
	m_needItemNum(NeedItemNum),
	m_useItemNum(0),
	m_enhanceStep(0),
	m_needMoney(FirstNeedMoney),
	m_enhanceType(enhanceType),
	m_wallet(wallet),
	m_enhanceTypeChoice(EnhanceType::EnhanceTypeChoice::EnhanceTheWorldTime)
{
}

//�X�V
void EnhanceTheWorldTime::Update()
{
	//�{���̍X�V����
	Actor::Update();

	//�������Ă������ƂɕK�v�f�ނ𑝂₷
	if (m_enhanceType->GetMaxTheWorldTime() >= 7)
	{
		m_enhanceStep = 1;
	}
	if (m_enhanceType->GetMaxTheWorldTime() >= 9)
	{
		m_enhanceStep = 2;
	}
	if (m_enhanceType->GetMaxTheWorldTime() >= 12)
	{
		m_enhanceStep = 3;
	}

	m_needMoney = NeedMoney[m_enhanceStep];

	//�{�^��
	m_button.Update(m_transform.position);
}

//�`��@
void EnhanceTheWorldTime::Draw()
{
	SetFontSize(30);
	DrawFormatString(510, 270,
		GetColor(255, 255, 255),
		"%d$",
		NeedMoney[m_enhanceStep]);

	SetFontSize(20);
	DrawFormatString(260, 305,
		GetColor(255, 255, 255),
		"�X�L���ő厞�ԁ�%.0f:�����と%.0f",
		m_enhanceType->GetMaxTheWorldTime(),
		m_enhanceType->GetMaxTheWorldTime() + m_enhanceType->AddMaxTheWroldTime);

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
void EnhanceTheWorldTime::OnClick()
{
	if (!CheckCondition()) return;

	//�����ɕK�v�ȃA�C�e��������
	m_chest->LostItem(m_useItemNum);
	m_wallet->LostMoney(m_needMoney);

	//����
	m_enhanceType->Enhance(m_enhanceTypeChoice);
}

//�{�^�����L�����ǂ����`�F�b�N
bool EnhanceTheWorldTime::CheckCondition()
{
	//���߂��l�܂ŋ���������I��
	if (m_enhanceType->GetMaxHaveInventory() < EndEnhanceCount)
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
				//�������狭��
				if (m_needItemNum == std::next(m_chest->GetItemList().begin(), i)->GetItemNum() &&
					m_needMoney <= m_wallet->HaveMoney())
				{
					m_canEnhance = true;
					m_useItemNum = i;
				}
				if (m_enhanceType->OnTheWorldTimeButton())
				{
					m_enhanceType->TheWorldButtonTimeReset();
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