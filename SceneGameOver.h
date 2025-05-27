#pragma once
#include "SceneBase.h"

class Node;

class SceneGameOver : public SceneBase
{
private:
	Node* m_rootNode;

	int m_movieGraphHandle;

public:
	// �R���X�g���N�^
	SceneGameOver() :
		m_rootNode(nullptr),
		m_movieGraphHandle(0) {};

	virtual void Initialize() override;		// ������
	virtual void Finalize() override;		// �I��
	virtual SceneBase* Update() override;	// �X�V
	virtual void Draw() override;			// �`��
};