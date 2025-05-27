#include"DrawStageView.h"
#include"ModelLoader.h"

DrawStageView::DrawStageView(const char* model)
{
	m_model = ModelLoader::LoadModel(model);

	// ���f���̕`��
	MV1DrawModel(m_model);
}

void DrawStageView::Draw()
{
	// ���f���̕`��
	MV1DrawModel(m_model);
}

void DrawStageView::Release()
{
	// �X�e�[�W�̃��f�����폜
	MV1DeleteModel(m_model);
}