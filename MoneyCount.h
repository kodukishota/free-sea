#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Transform.h"
#include "Sprite.h"

class Wallet;

class MoneyCount : public Node
{
private:
	static constexpr int RestDays = 3;	//�c��̓��t�̏����l
	static constexpr int NeedMoney = 200;	//�ŏ��ɕK�v�Ȃ���
	static constexpr Vector2 UiPos = Vector2(125, 250);
	static constexpr Vector2 FontSize = Vector2(20, 35);	// ����1�����̕��E����
	static constexpr int FontMargin = 5;					// �����Ɛ����̊Ԃ̗]��
	static constexpr int AddNeedMoney = 100;

	int m_needMoney;
	int m_restDays;

	bool m_taskClear;	//�������i������
	int m_clearCount;	//����N���A������

	bool m_backMenu;	//���j���[��ʂɗ�����

	Wallet* m_wallet;

	int m_fontTextureId;	// �����t�H���g
	Sprite m_moneyCountUi;
	Transform m_transform;

	bool m_isClear;

protected:
	virtual void Load();
	virtual void Release();
	virtual void Update();
	virtual void Draw() override;

public:
	MoneyCount(Wallet* wallet, int restDays, int clearCount);

	int GetRestDays()
	{
		return m_restDays;
	}

	int GetClearCount()
	{
		return m_clearCount;
	}

	int GetNeedMoney()
	{
		return m_needMoney;
	}

	bool GetTaskClear() const
	{
		return m_taskClear;
	}

	void BackMenu()
	{
		m_backMenu = true;
	}

	void AddClearCount()
	{
		m_clearCount++;
	}
};