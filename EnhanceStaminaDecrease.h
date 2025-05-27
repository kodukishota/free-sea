#pragma once
#include "Button.h"
#include "Actor.h"
#include "SceneBase.h"
#include "Vector2.h"
#include "EnhanceType.h"
#include <vector>

class Chest;
class EnhanceType;
class Wallet;

class EnhanceStaminaDecrease : public Actor
{
private:
	static constexpr Vector2 Position = Vector2(750, 400);
	static constexpr Vector2 Size = Vector2(320, 100);
	static constexpr int FirstNeedMoney = 100;				//�K�v�Ȃ����̏�����
	static constexpr int NeedMoney[4] = { 150, 250, 350, 450};	//�������Ă������Ƃɏオ���Ă����K�v�Ȃ���
	static constexpr int EndEnhanceCount = 10;		//�����܂ł̐��l����������I���
	static constexpr int NeedItemNum = 2;	//�K�v�ȃA�C�e���̔ԍ�

	int m_needMoney;		//�K�v�Ȃ���
	int m_enhanceStep;		//�ǂꂾ������������

	bool m_canEnhance;		//�����ł��邩

	int m_needItemNum;		//�����ɕK�v�ȃA�C�e���̃i���o�[

	Chest* m_chest;

	int m_useItemNum;		//�g�����A�C�e�������ԖڂɎ����Ă�����


protected:
	EnhanceType::EnhanceTypeChoice m_enhanceTypeChoice;	//�����ꂽ���ɋ����������
	Button m_button;	//�{�^���@�\

	EnhanceType* m_enhanceType;
	Wallet* m_wallet;

	//�{�^���������ꂽ���ɌĂ΂��R�[���o�b�N�֐�
	void OnClick();

	//�{�^�����L�����ǂ������`�F�b�N
	virtual bool CheckCondition();

	virtual void Update() override;	//�X�V
	virtual void Draw() override;	//�`��

public:
	EnhanceStaminaDecrease(Chest* chest, Wallet* wallet, EnhanceType* enhanceType);
};