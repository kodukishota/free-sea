#pragma once
#include "Node.h"
#include "Transform.h"
#include "Sprite.h"

class LoadPlayer;

class Wallet : public Node
{
private:
	static constexpr Vector2 WalletSize = Vector2(40, 11);	// SCORE�摜�̕��E����
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr Vector2 WalletPos = Vector2(210, 80);		// ��ʉE�ォ��̍���
	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��

	Sprite m_walletImg;		// Wallet�摜
	int m_fontTextureId;	// �����t�H���g
	Transform m_transform;	// �p��
	int m_haveMoney;		// �X�R�A�̒l

	LoadPlayer* m_player;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	// �R���X�g���N�^
	Wallet(LoadPlayer* player);

	/*
	// ���W��ݒ�
	void SetPosition(const Vector2& position)
	{
		m_transform.position = position;
	}
	*/

	void InWalletMoney(int money)
	{
		m_haveMoney += money;
	}

	void LostMoney(int money)
	{
		m_haveMoney -= money;
	}

	//�������Ă��邨��
	int HaveMoney() const
	{
		return m_haveMoney;
	}
};
