#pragma once
#include "Button.h"
#include "Actor.h"
#include "SceneBase.h"
#include "Vector2.h"

class LoadPlayer;
class Inventory;

class SellButton : public Actor
{
private:
	static constexpr Vector2 Position = Vector2(210, 500);
	static constexpr Vector2 Size = Vector2(200, 100);

	bool m_checkOnClick;

	LoadPlayer* m_player;
	Inventory* m_inventory;

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
	SellButton(LoadPlayer* player, Inventory* inventory);

	bool GetCheckOnClick()
	{
		return m_checkOnClick;
	}
};
