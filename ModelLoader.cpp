#include"ModelLoader.h"
#include<string>

// ���f���̓ǂݍ���
int ModelLoader::LoadModel(const char* model)
{
	std::string fullPath;
	fullPath += "Resource/";
	fullPath += model;
	return MV1LoadModel(fullPath.c_str());
}

// �A�j���[�V�����̓ǂݍ���
int ModelLoader::LoadAnim(const char* anim)
{
	return MV1LoadModel(anim);
}

// �A�j���[�V�����̃A�^�b�`
int ModelLoader::AttachAnim(const int& model, const int& animId)
{
	return MV1AttachAnim(model, 0, animId);
}
