#pragma once
#include "Button.h"
#include "Actor.h"
#include "SceneBase.h"
#include "Vector2.h"

class LoadPlayer;

class EatButton : public Actor
{
private:
	static constexpr Vector2 Position = Vector2(200, 650);
	static constexpr Vector2 Size = Vector2(200, 100);

	bool m_checkOnClick;

	float m_time;
	bool m_checkClick;


	LoadPlayer* m_player;

protected:
	Button m_button;	//ボタン機能	

	//ボタンが有効かどうかをチェック
	virtual bool CheckCondition();

	//ボタンが押された時に呼ばれるコールバック関数
	void OnClick();

	virtual void Update() override;	//更新
	virtual void Draw() override;	//描画

public:
	EatButton(LoadPlayer* player);

	bool GetCheckOnClick()
	{
		return m_checkOnClick;
	}
};