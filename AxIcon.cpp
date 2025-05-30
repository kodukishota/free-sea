#include "AxIcon.h"
#include "Inventory.h"
#include "Screen.h"
#include "Ax.h"

AxIcon::AxIcon(Ax* ax) : 
	m_rightX(GaugeRight),
	m_ax(ax),
	m_Durability(0)
{
	m_axIconUi.Register("ax_icon.png");

	m_axIconTsransform.position = Vector2(60, 890);
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


	// Œ»Ý‚Ì‘Ï‹v—Í€‘Ï‹v—Í‚ÌÅ‘å’l‚ÅŽc‘Ï‹v—Í‚Ì”ä—¦‚ðŒvŽZ
	m_Durability = m_ax->GetDurability() / m_ax->GetMaxDurability();


	m_rightX = static_cast<int>(GaugeLeft + (GaugeWidth * m_Durability));

	if (m_rightX <= GaugeLeft)
	{
		m_rightX = GaugeLeft;
	}
}

void AxIcon::Draw()
{	
	// Œ»Ý‚Ì‘Ï‹v—ÍƒQ[ƒW
	DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	// ‘Ï‹v—ÍƒQ[ƒW‚Ì”wŒi
	DrawBox(GaugeRight, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(100, 100, 100), true);

	m_axIconUi.Draw(m_axIconTsransform);
}