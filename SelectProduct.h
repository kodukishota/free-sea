#pragma once
#include "Button.h"
#include "Actor.h"
#include "SceneBase.h"
#include "Vector2.h"

class LoadPlayer;

class SelectProduct : public Actor
{
private:
	static constexpr Vector2 Size = Vector2(200, 100);

	bool m_checkOnClick;

	int m_productNum;	//なんの商品か

	Vector2 m_position;
	LoadPlayer* m_player;

protected:
	Button m_button;	//ボタン機能	


	//ボタンが押された時に呼ばれるコールバック関数
	void OnClick();

	virtual void Update() override;	//更新
	virtual void Draw() override;	//描画

public:
	SelectProduct(LoadPlayer* player,
		Vector2 position,
		int productNum,
		char* iconName);

	bool GetCheckOnClick()
	{
		return m_checkOnClick;
	}

	int GetProductNum()
	{
		return m_productNum;
	}
};
