#pragma once
#include"Sprite.h"
#include"Vector2.h"
#include"Screen.h"
#include"Node.h"

class ItemFactory;

class UiResult : public Node
{
private:
	static constexpr float ShowBackGroundTime = 1.0f;	// �g�傳����̂ɂ����鎞��
	static constexpr float StartBackGroundScale = 0.0f;	// �w�i�̊g��O�̃T�C�Y
	static constexpr float EndBackGroundScale = 1.0f;	// �w�i�̊g���̃T�C�Y
	static constexpr Vector2 BackGroundPos = Vector2(Screen::Center);	// �w�i�̈ʒu

	float m_elapsedTime;
	Sprite m_backGround;	// ���U���g��ʂ̔w�i�摜
	Sprite m_clearTime;		// �N���A�^�C���i���ږ��j�̉摜
	Sprite m_returnTitle;	// �^�C�g���ɖ߂邽�߂̎w��������摜

	Transform m_backGroundTransform;
	Transform m_timeTransform;
	Transform m_returnTransform;

	ItemFactory* m_itemFactory;

	bool m_showedBack;	// �w�i���\������Ă��邩�ǂ���

	bool m_showTimeFlg;
	bool m_showPressFlg;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	UiResult(ItemFactory* itemFactory);

	// ���U���g��ʂ�\�����I��������ǂ���
	bool IsShowedPress()
	{
		return m_showPressFlg;
	}
};
