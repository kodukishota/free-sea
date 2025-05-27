#pragma once
#include "SceneBase.h"

class Node;
class Chest;
class MoneyCount;
class Wallet;
class EnhanceType;

// �^�C�g���V�[��
class SceneTitle : public SceneBase
{
private:
	Node* m_rootNode;
	int m_bgm;
	int m_seClick;

	Chest* m_chest;
	MoneyCount* m_moneyCount;
	Wallet* m_wallet;
	EnhanceType* m_enhanceType;

	static constexpr int FirstMaxHaveItem = 3;		//�ŏ��ɃA�C�e�������Ă鐔�̍ő��
	static constexpr int FirstMaxHaveWeight = 50;	//�ŏ��Ɏ��Ă�ő�e��
	static constexpr float FirstTheWorldTime = 5;	//�ŏ��̃U���[���h�̌p������
	static constexpr int FirstTheWorldCount = 1;	//�ŏ��ɃU���[���h�ł����
	static constexpr float StaminaRecoveryAmount = 10;	// �X�^�~�i�̉񕜗�
	static constexpr float StaminaDecreaseAmount = 20;	// �X�^�~�i�̏����


public:
	// �R���X�g���N�^
	SceneTitle() :
		m_rootNode(nullptr),
		m_bgm(0),
		m_seClick(0),
		m_chest(nullptr),
		m_wallet(nullptr),
		m_moneyCount(nullptr),
		m_enhanceType(nullptr){}

	virtual void Initialize() override;		// ������
	virtual void Finalize() override;		// �I��
	virtual SceneBase* Update() override;	// �X�V
	virtual void Draw() override;			// �`��
};
