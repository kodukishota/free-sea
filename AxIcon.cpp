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


	// ���݂̑ϋv�́��ϋv�͂̍ő�l�Ŏc�ϋv�͂̔䗦���v�Z
	m_Durability = m_ax->GetDurability() / m_ax->GetMaxDurability();


	m_rightX = static_cast<int>(GaugeRight - (GaugeWidth * m_Durability));
}

void AxIcon::Draw()
{	
	// �ϋv�̓Q�[�W�̔w�i
	DrawBox(GaugeLeft, GaugeY, GaugeRight, GaugeY + GaugeHeight, GetColor(100, 100, 100), true);
	// ���݂̑ϋv�̓Q�[�W�i�����ɏk�ށj
	DrawBox(GaugeLeft, GaugeY, m_rightX, GaugeY + GaugeHeight, GetColor(255, 255, 255), true);
	

	m_axIconUi.Draw(m_axIconTsransform);
}