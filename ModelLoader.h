#pragma once
#include"Vector3.h"
#include"DxLib.h"

class ModelLoader
{
private:

public:
	static int LoadModel(const char* model);	// ���f���̓ǂݍ���
	static int LoadAnim(const char* anim);		// �A�j���[�V�����̓ǂݍ���
	static int AttachAnim(const int& model, const int& animId);	// �A�j���[�V�����̃A�^�b�`
};