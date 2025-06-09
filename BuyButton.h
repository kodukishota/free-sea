#pragma once
#include "Button.h"
#include "Actor.h"
#include "SceneBase.h"
#include "Vector2.h"

class LoadPlayer;
class Wallet;
class TredeUi;

class BuyButton : public Actor
{
private:
	static constexpr Vector2 Position = Vector2(1220, 760);
	static constexpr Vector2 Size = Vector2(200, 100);

	bool m_checkOnClick;

	int m_needMoney;

	LoadPlayer* m_player;
	Wallet* m_wallet;
	TredeUi* m_tredeUi;


	float m_time;
	bool m_checkClick;

protected:
	Button m_button;	//ボタン機能	

	//ボタンが有効かどうかをチェック
	virtual bool CheckCondition();

	//ボタンが押された時に呼ばれるコールバック関数
	void OnClick();

	virtual void Update() override;	//更新
	virtual void Draw() override;	//描画

public:
	BuyButton(LoadPlayer* player,Wallet* wallet,TredeUi* tredeUi);

	bool GetCheckOnClick()
	{
		return m_checkOnClick;
	}
};
