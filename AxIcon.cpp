#include "AxIcon.h"
#include "Inventory.h"
#include "Screen.h"
#include "Ax.h"
#include "LoadPlayer.h"

AxIcon::AxIcon(Ax* ax,int haveCount,LoadPlayer* player, Inventory* inventory) :
	m_rightX(GaugeRight),
	m_ax(ax),
	m_Durability(0),
	m_haveCount(haveCount),
	m_player(player),
	m_inventory(inventory)
{
	m_axIconUi.Register("ax_icon.png");	
}

void AxIcon::Load()
{
	m_axIconUi.Load();
}

void AxIcon::Release()
{
	m_axIconUi.Release();
}

void AxIcon::Update()
{
	m_axIconUi.Update();

	if (m_inventory->GetBreakAx())
	{
		ShiftDrawPos();

		m_inventory->AddShiftIconCount();
	}

	// Œ»İ‚Ì‘Ï‹v—Í€‘Ï‹v—Í‚ÌÅ‘å’l‚Åc‘Ï‹v—Í‚Ì”ä—¦‚ğŒvZ
	m_Durability = m_ax->GetDurability() / m_ax->GetMaxDurability();

	if (!m_player->GetIsMenu())
	{
		m_axIconTsransform.position = SetPos + (Vector2(100,0) * m_haveCount);

		m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_Durability));
	}
	else
	{
		m_axIconTsransform.position = IsMenuSetPos + (Vector2(100, 0) * m_haveCount);

		m_rightX = static_cast<int>(InMenuGaugeLeft + (InMenuGaugeWidth * m_Durability));
	}	

	m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_Durability));

	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeLeft;
	}

	m_ax->SetDrawPos(m_axIconTsransform.position);
}

void AxIcon::Draw()
{	
	if (!m_player->GetIsMenu())
	{
		// Œ»İ‚Ì‘Ï‹v—ÍƒQ[ƒW
		DrawBox(GaugeLeft + (100 * m_haveCount), GaugeY, GaugeRight + (100 * m_haveCount), GaugeY + GaugeHeight, 
			GetColor(255, 255, 255), true);
		// ‘Ï‹v—ÍƒQ[ƒW‚Ì”wŒi
		DrawBox(GaugeRight + (100 * m_haveCount), GaugeY, m_rightX + (100 * m_haveCount), GaugeY + GaugeHeight,
			GetColor(100, 100, 100), true);
	}
	else
	{
		// Œ»İ‚Ì‘Ï‹v—ÍƒQ[ƒW
		DrawBox(InMenuGaugeLeft + (100 * m_haveCount), InMenuGaugeY, InMenuGaugeRight + (100 * m_haveCount), InMenuGaugeY + GaugeHeight,
			GetColor(255, 255, 255), true);
		// ‘Ï‹v—ÍƒQ[ƒW‚Ì”wŒi
		DrawBox(InMenuGaugeRight + (100 * m_haveCount), InMenuGaugeY, m_rightX + (100 * m_haveCount), InMenuGaugeY + GaugeHeight,
			GetColor(100, 100, 100), true);
	}

	m_axIconUi.Draw(m_axIconTsransform);
}