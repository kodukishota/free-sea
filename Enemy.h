#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"NavMesh.h"
#include"DxLib.h"
#include<vector>
#include <thread>
#include <atomic>

class Animation3D;
class LoadPlayer;
class CheckRoot;

class Enemy : public Actor3D
{
public:
	enum class Anim
	{
		Idle,
		Run,

		Attack,

		Length,
	};

private:
	static constexpr int AnimNum = static_cast<int>(Anim::Length);	// �A�j���[�V�����̐�
	static constexpr float MoveSpeedCombat = 5.5f;	// �v���C���[�������̈ړ����x
	static constexpr float MoveSpeed = 2.0f;	// �p�j���̈ړ����x
	static constexpr float Width = 300.0f;	// �G�̕�
	static const char* AnimList[AnimNum];
	static constexpr Vector3 FindColSize = Vector3(900, 200, 900);	// �v���C���[�������邽�߂̓����蔻��̃T�C�Y
	static constexpr Vector3 AttackColSize = Vector3(300, 200, 300);	// �U������̃T�C�Y
	static constexpr Vector3 ColOffset = Vector3(0, 100, 0);	// �R���C�_�[�̃I�t�Z�b�g
	static constexpr int Power = 10;		// �U����
	static constexpr float CoolTime = 1.0f;	// �U����̃N�[���^�C��

	std::vector<Animation3D*> m_attachAnimList;
	int m_model;	// �G�̃��f��
	int m_animIndex;	// �Đ����̃A�j���[�V����
	Vector3 m_enemyPos;
	Vector3 m_enemyPastPos;

	// �A�j���[�V�����؂�ւ��p
	Anim m_nowAnim;
	Anim m_nextAnim;

	// ���f���̉�]�p
	Vector3 m_moveDirection;

	//static const char* AnimList[AnimNum];	// �A�j���[�V�������w�肷��p
	NavMesh* m_navMesh;	// �o�H�T���p
	LoadPlayer* m_player;	// �v���C���[

	bool m_isSet;
	bool m_isMove;	// �p�j�� && �ړI�n�Ɍ������Ă���r����
	bool m_isFind;	// �v���C���[����������
	bool m_isAttack;	// �U�����ɗ����~�܂�Ȃ炱�̃t���O���g��
	bool m_countCoolTime;	// �N�[���^�C���J�E���g�J�n�t���O
	float m_durationCoolTime;	// �N�[���^�C���̌o�ߎ���
	CheckRoot* m_checkRoot;	// �X�e�[�W��񂩂�o�H�T�����s���p
	int m_polyCount;	// �ړI�n�܂ł̃|���S����
	bool m_isCheck;		// �v���C���[�������A�v���C���[�܂ł̒T�����I����Ă��邩
	bool m_pastAttackFlg;	// �U�����ɍĒT�����s���p

	bool m_stoped;	// �O�̃t���[���œ������~�߂��Ă�����

	std::thread* m_thread = nullptr;
	bool m_found = false;	// �T�����I��������ǂ���

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void OnCollision(const Actor3D* other) override;

public:
	Enemy(NavMesh* navMesh, const Vector3& pos, LoadPlayer* loadPlayer);

	// �A�j���[�V������؂�ւ���(Lerp)
	void ChangeAnimLerp();

	// �A�j���[�V������؂�ւ���(����)
	void ChangeAnimQuick(const Anim nextAnim);

	// �A�j���[�V�������Đ�����
	void PlayAnim();

	// �G�̈ړ��i�Ր�Ԑ��j
	void MoveCombat();

	// �G�̈ړ��i�p�j�j
	void MoveWanderAround();

	// �G�̍U��
	void Attack();

	// �G�̈ʒu��Ԃ�
	Vector3 EnemyPos()
	{
		return m_enemyPos;
	}
};
