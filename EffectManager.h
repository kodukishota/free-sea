#pragma once
#include <EffekseerForDXLib.h>
#include "Vector3.h"

// �G�t�F�N�g�Ǘ��N���X
class EffectManager
{
private:
	static constexpr int EffectParticleLimit = 20000;	// ��ʂɕ\���ł���ő�p�[�e�B�N����

public:
	//�V���O���g��
	static EffectManager* GetInstance()
	{
		static EffectManager instance;
		return &instance;
	}

	void Initialize();					// ������
	int Load(const char* filePath, float = 1.0f);		// �ǂݍ���
	void Update();						// �X�V
	void Draw();						// �`��
};