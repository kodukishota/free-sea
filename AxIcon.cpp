#include "AxIcon.h"
#include "Inventory.h"
#include "Screen.h"
#include "Ax.h"

AxIcon::AxIcon(Ax* ax,int haveCount) : 
	m_rightX(GaugeRight),
	m_ax(ax),
	m_Durability(0),
	m_haveCount(haveCount)
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


	// Œ»İ‚Ì‘Ï‹v—Í€‘Ï‹v—Í‚ÌÅ‘å’l‚Åc‘Ï‹v—Í‚Ì”ä—¦‚ğŒvZ
	m_Durability = m_ax->GetDurability() / m_ax->GetMaxDurability();

	m_axIconTsransform.position = Vector2(60, 890) + (Vector2(100,0) * m_haveCount);

	m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_Durability));

	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeLeft;
	}

	m_ax->SetDrawPos(m_axIconTsransform.position);
}

void AxIcon::Draw()
{	
	// Œ»İ‚Ì‘Ï‹v—ÍƒQ[ƒW
	DrawBox(GaugeLeft + (100 * m_haveCount), GaugeY, GaugeRight + (100 * m_haveCount), GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	// ‘Ï‹v—ÍƒQ[ƒW‚Ì”wŒi
	DrawBox(GaugeRight + (100 * m_haveCount), GaugeY, m_rightX + (100 * m_haveCount), GaugeY + GaugeHeight, GetColor(100, 100, 100), true);

	m_axIconUi.Draw(m_axIconTsransform);
}