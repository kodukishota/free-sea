#include "MoneyCount.h"
#include "Screen.h"
#include "ImageLoader.h"
#include "Wallet.h"
#include "Input.h"
#include <DxLib.h>

MoneyCount::MoneyCount(Wallet* wallet, int restDays, int clearCount) :
	m_needMoney(NeedMoney),
	m_restDays(restDays),
	m_wallet(wallet),
	m_clearCount(clearCount),
	m_fontTextureId(0),
	m_taskClear(false),
	m_backMenu(false),
	m_isClear(false)
{
	m_transform.position = UiPos;
	m_transform.scale = 0.3f;
	m_moneyCountUi.Register("money_count_ui.png");

	if (m_clearCount > 0)
	{
		m_needMoney += AddNeedMoney * m_clearCount;
	}	
}

void MoneyCount::Load()
{
	m_moneyCountUi.Load();
	m_fontTextureId = ImageLoader::GetInstance()->Load("score_font.png");
}

void MoneyCount::Release()
{
	m_moneyCountUi.Release();
	ImageLoader::GetInstance()->Delete("score_font.png");
}

void MoneyCount::Update()
{
	m_moneyCountUi.Update();

	if (m_restDays <= 0)
	{
		if (Input::GetInstance()->IsKeyDown(KEY_INPUT_M))
		{
			if (m_wallet->HaveMoney() >= m_needMoney && !m_isClear)
			{
				m_taskClear = true;
				m_clearCount++;

				m_isClear = true;
			}
			if (m_wallet->HaveMoney() <= m_needMoney)
			{
				m_taskClear = false;
				m_isClear = false;
			}
		}
	}

	if (m_backMenu)
	{
		m_restDays--;
		m_backMenu = false;
	}

	if (m_restDays < 0)
	{
		m_restDays = RestDays;
	}
}

void MoneyCount::Draw()
{
	m_moneyCountUi.Draw(m_transform);

	//�c������̕`��
	Vector2 restDaysTxetPos = m_transform.position + Vector2(50, -105);
	restDaysTxetPos.y += FontMargin;
	int restDays = m_restDays;
	int restDaysDigit = 1;
	do
	{
		int value = restDays % 10;	// 1�̈ʂ̒l�����o��

		DrawRectGraph(
			static_cast<int>(restDaysTxetPos.x - FontSize.x * restDaysDigit), static_cast<int>(restDaysTxetPos.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		restDays /= 10;	// �X�R�A�̌�����
		restDaysDigit++;		// ���̌���
	} while (restDays > 0);

	//�K�v�Ȃ����̕`��
	Vector2 needMoneyTxetPos = m_transform.position + Vector2(80, -20);
	needMoneyTxetPos.y += FontMargin;
	int needMoney = m_needMoney;
	int needMoneyDigit = 1;
	do
	{
		int value = needMoney % 10;	// 1�̈ʂ̒l�����o��

		DrawRectGraph(
			static_cast<int>(needMoneyTxetPos.x - FontSize.x * needMoneyDigit), static_cast<int>(needMoneyTxetPos.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		needMoney /= 10;	// �X�R�A�̌�����
		needMoneyDigit++;		// ���̌���
	} while (needMoney > 0);

	//���݂̉߂������T�̕`��
	Vector2 clearCountTxetPos = m_transform.position + Vector2(50, 65);
	clearCountTxetPos.y += FontMargin;
	int clearCount = m_clearCount;
	int clearCountDigit = 1;
	do
	{
		int value = clearCount % 10;	// 1�̈ʂ̒l�����o��

		DrawRectGraph(
			static_cast<int>(clearCountTxetPos.x - FontSize.x * clearCountDigit), static_cast<int>(clearCountTxetPos.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		clearCount /= 10;	// �X�R�A�̌�����
		clearCountDigit++;		// ���̌���
	} while (clearCount > 0);
}