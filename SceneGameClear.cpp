#include "SceneGameClear.h"
#include "SceneTitle.h"
#include "Input.h"
#include "PressAny.h"
#include "Node.h"
#include "Screen.h"	
#include "DxLib.h"

void SceneGameClear::Initialize()
{
	m_rootNode = new Node();

	// ”wŒi
	m_rootNode->AddChild(new Actor(
		"Background",
		"game_clear.png",
		Screen::Center
	));

	// PressAnyButton
	m_rootNode->AddChild(new Actor(
		"PressAny",
		"press_any_button.png",
		Screen::BottomCenter - Vector2(0, Screen::Height / 4)
	));
}

void SceneGameClear::Finalize()
{
	m_rootNode->TreeRelease();

	delete m_rootNode;
	m_rootNode = nullptr;

	DeleteGraph(m_movieGraphHandle);
}

SceneBase* SceneGameClear::Update()
{
	if (Input::GetInstance()->IsAnyKeyDown())
	{
		return new SceneTitle();
	}

	m_rootNode->TreeUpdate();

	return this;
}

void SceneGameClear::Draw()
{
	m_rootNode->TreeDraw();

	DrawExtendGraph(0, 0, 1280, 960, m_movieGraphHandle, FALSE);
}