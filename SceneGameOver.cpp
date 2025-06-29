#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "Input.h"
#include "PressAny.h"
#include "Node.h"
#include "Screen.h"	
#include "DxLib.h"

void SceneGameOver::Initialize()
{
	m_rootNode = new Node();

	// ”wŒi
	m_rootNode->AddChild(new Actor(
		"Background",
		"game_over.png",
		Screen::Center
	));

	// PressAnyButton
	m_rootNode->AddChild(new Actor(
		"PressAny",
		"press_any_button.png",
		Screen::BottomCenter - Vector2(0, Screen::Height / 4)
	));
}

void SceneGameOver::Finalize()
{
	m_rootNode->TreeRelease();

	delete m_rootNode;
	m_rootNode = nullptr;

	DeleteGraph(m_movieGraphHandle);
}

SceneBase* SceneGameOver::Update()
{
	if (Input::GetInstance()->IsAnyKeyDown())
	{
		return new SceneTitle();
	}

	m_rootNode->TreeUpdate();

	return this;
}

void SceneGameOver::Draw()
{
	m_rootNode->TreeDraw();

	DrawExtendGraph(0, 0, 1280, 960, m_movieGraphHandle, FALSE);
}