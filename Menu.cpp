#include "Menu.h"
#include "Screen.h"
#include "Input.h"
#include "LoadPlayer.h"
#include "DxLib.h"

Menu::Menu(LoadPlayer* player) : 
	m_player(player)
{
	m_brackImg.Register("black_filter.png");
	m_background.Register("background.png");
	m_transform.position = Screen::Center;
}

void Menu::Load()
{
	m_brackImg.Load();
	m_background.Load();
}

void Menu::Release()
{
	m_brackImg.Release();
	m_background.Release();
}

void Menu::Update() 
{
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_TAB) && !m_player->GetNowTrede())
	{
		m_player->SwitchIsMenu();
	}

	m_brackImg.Update();
	m_background.Update();
}

void Menu::Draw()
{
	if (m_player->GetIsMenu())
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		m_brackImg.Draw(m_transform);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

		m_background.Draw(m_transform);
	}
}