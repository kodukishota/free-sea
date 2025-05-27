#pragma once

class SceneManager;
class Chest;

// �Q�[�����C�����[�v�N���X
class GameMain
{
private:
	SceneManager* m_sceneManager;	// �V�[���J��
	int m_screen;	// ����X�N���[��

	Chest* m_chest;

public:
	// �R���X�g���N�^
	GameMain() :
		m_sceneManager(nullptr),
		m_screen(0),

		m_chest(nullptr)
	{
		// �������Ȃ�
	}

	// �f�X�g���N�^
	virtual ~GameMain();
	
	// ���C�����[�v���s
	void Run();
};