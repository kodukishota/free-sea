#pragma once
#include"Node.h"

// �X�e�[�W�̌����ڂ�����\������
class DrawStageView : public Node
{
private:
	int m_model;

protected:
	virtual void Draw() override;
	virtual void Release() override;

public:
	DrawStageView(const char* model);

};