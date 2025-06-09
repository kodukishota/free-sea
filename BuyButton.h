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
	Button m_button;	//�{�^���@�\	

	//�{�^�����L�����ǂ������`�F�b�N
	virtual bool CheckCondition();

	//�{�^���������ꂽ���ɌĂ΂��R�[���o�b�N�֐�
	void OnClick();

	virtual void Update() override;	//�X�V
	virtual void Draw() override;	//�`��

public:
	BuyButton(LoadPlayer* player,Wallet* wallet,TredeUi* tredeUi);

	bool GetCheckOnClick()
	{
		return m_checkOnClick;
	}
};
