#include "Ax.h"
#include "Quaternion.h"
#include "LoadPlayer.h"
#include "Camera.h"
#include "Input.h"
#include "SkillCheak.h"
#include "AxIcon.h"
#include "Inventory.h"

Ax::Ax(LoadPlayer* player, SkillCheck* skillCheck, int haveCount,int axId,Inventory* inventory) : Actor3D("Ax"),
	m_durabilityValue(FirstDurabilityValue),
	m_attackDamage(AttackDamage),
	m_consumptionDurability(ConsumptionDurability[axId]),
	m_player(player),
	m_isCutTreeFlag(false),
	m_skillCheck(skillCheck),
	m_seCut(0),
	m_cutTreeValue(CutTreeValue[axId]),
	m_axId(axId),
	m_haveCount(haveCount),
	m_inventory(inventory)
{	
	m_axIcon = new AxIcon(this, m_haveCount,m_player,m_inventory);

	AddChild(m_axIcon);
}

void Ax::Load()
{
	Actor3D::Load();

	m_seCut = LoadSoundMem("Resource/sound/cut_tree_se.mp3");
	ChangeVolumeSoundMem(128, m_seCut);
}

void Ax::Release()
{
	DeleteSoundMem(m_seCut);

	Actor3D::Release();
}

void Ax::Update()
{
	m_transform.position = m_player->GetPosition() + GodSetPos;

	Actor3D::Update();
}

void Ax::Draw()
{
#ifdef _DEBUG
		DrawFormatString(0, 350, GetColor(255, 255, 255),
			"‘Ï‹v%f",
			m_durabilityValue
		);

#endif // _DEBUG

	Actor3D::Draw();
}

void Ax::CutTree()
{
	if (m_skillCheck->GetIsClick())
	{
		m_cutTreeValue = CutTreeValue[m_axId];
		m_consumptionDurability = ConsumptionDurability[m_axId];

		PlaySoundMem(m_seCut, DX_PLAYTYPE_BACK);

		//‰Ÿ‚µ‚½ˆÊ’u‚ªGood‚âPerfect‚Ì’†‚Å‰Ÿ‚³‚ê‚Ä‚¢‚é‚©
		if (m_skillCheck->GetPrefectFlag())
		{
			m_consumptionDurability = m_consumptionDurability * 0.5f;
			m_cutTreeValue *= 1.5f;

			m_skillCheck->ResetPrefectFlag();
		}
		else if (m_skillCheck->GetGoodFlag())
		{
			m_consumptionDurability = m_consumptionDurability;
			m_cutTreeValue *= 1;

			m_skillCheck->ResetGoodFlag();
		}
		else if(m_skillCheck->GetBadFlag())
		{
			 m_consumptionDurability = m_consumptionDurability * 1.5f;
			 m_cutTreeValue *= 0.5f;

			 m_skillCheck->ResetBadFlag();
		}

		m_durabilityValue -= m_consumptionDurability;

		m_isCutTreeFlag = true;

		m_skillCheck->ResetIsClick();
	}
}