#pragma once
#include "SceneBase.h"

class Node;

class SceneGameClear : public SceneBase
{
private:
	Node* m_rootNode;

	int m_movieGraphHandle;

public:
	// �R���X�g���N�^
	SceneGameClear() :
		m_rootNode(nullptr),
		m_movieGraphHandle(0) {
	};

	virtual void Initialize() override;		// ������
	virtual void Finalize() override;		// �I��
	virtual SceneBase* Update() override;	// �X�V
	virtual void Draw() override;			// �`��
};