#pragma once
#include "Node.h"
#include "Vector3.h"

class Effect : Node
{
private:
	static constexpr float EffectMoveSpeed = 0.2f;	//�G�t�F�N�g���ړ����鑬�x

	int m_effectPlayInterval;	//�G�t�F�N�g���Đ��������
	int m_effectHandle;			//�G�t�F�N�g�̃��\�[�X�p
	int m_playingEffectHandle;	//�Đ����̃G�t�F�N�g�n���h��
	int m_playCount;

public:
	//�R���X�g���N�^
	Effect(const char* filePath, const float effectSize, const int playInterval = 150);

	// �f�X�g���N�^
	~Effect();						

	void Update(const Vector3& position = Vector3());		// �X�V
	void Play(bool loop = true);							// �Đ�
	void Stop();											// �Đ����̃G�t�F�N�g���~����
};