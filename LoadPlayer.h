#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"DxLib.h"
#include<vector>

class Camera;
class Animation3D;
class CollisionStage;
class Inventory;
class EnhanceType;
class ItemFactory;

class LoadPlayer : public Actor3D
{
public:
	// �A�j���[�V����
	enum class Anim
	{
		Idle,
		Walk,
		Run,
		Death,

		Length,
	};

private:
	std::vector<Animation3D*> m_attachAnimList;

	static constexpr int AnimNum = static_cast<int>(Anim::Length);	// �A�j���[�V�����̐�

	static constexpr float WalkSpeed = 4.0f;	// �������x
	static constexpr float RunSpeed = 12.0f;	// ���鑬�x
	static constexpr float WeightOverSpeed = 6.0f;	//�e�ʃI�[�o�[�����Ƃ��̑��鑬�x
	static constexpr float RotateSpeed = 10.0f;	// ��]���x
	static constexpr float DurationTime = 1.0f;
	static constexpr float JumpPower = 4.0f;	// �����x
	static constexpr float Gravity = 9.8f;		// �d�͉����x
	static constexpr Vector3 SpawnPos = Vector3(850, 100, 850);	// �X�e�[�W�ɃX�|�[������ꏊ
	static constexpr Vector3 ColOffset = Vector3(0, 90, 0);	// �R���C�_�[�̃I�t�Z�b�g
	static constexpr Vector3 ColSize = Vector3(150, 180, 150);	// �R���C�_�[�̃T�C�Y
	static constexpr int MaxHp = 100;	// �̗͂̍ő�l
	static constexpr float TheWorldCoolDown = 30;		//�X�L���̃N�[���_�E��

	// �X�^�~�i�֘A
	static constexpr float MaxStamina = 100;	// ����̂ɕK�v�ȃX�^�~�i�̍ő�l
	static constexpr float StaminaRecoveryAmount = 10;	// �X�^�~�i�̉񕜗�
	static constexpr float StaminaDecreaseAmount = 20;	// �X�^�~�i�̏����
	static constexpr float TimeToRecoverStamina = 1;	// �X�^�~�i���񕜂��n�߂�܂ł̎���

	Vector3 AxisY = Vector3(0.0f, 1.0f, 0.0f);	// ��]��(Y���ŏ����)

	static const char* AnimList[AnimNum];

	int m_model;	// �v���C���[�̃��f��(mv1)

	int m_animIndex;	// �Đ����̃A�j���[�V����

	float m_runSpeed;
	bool m_isJump;
	bool m_isJumping;
	bool m_isFall;	// ���ݗ������Ă��邩
	bool m_isFloating;
	float m_fallStartY;	// �������n�߂̍���

	int m_maxHaveWeight;	//���Ă�ő�e��
	bool m_weightOver;		//���Ă�ő�e�ʂ���������

	//���Ԓ�~�Ɋւ���ϐ�
	int m_useTheWorldCount;	//����g������
	float m_theWorldCoolDown;
	float m_nowStopTime;	//���Ԓ�~���Ă��牽�b�o������
	float m_stopTime;		//���Ԓ�~�ł��鎞��
	bool m_isStop;			//���Ԓ�~���Ă邩
	bool m_isCooldown;		// �N�[���_�E������

	bool m_isGetting;	//�A�C�e�����E������

	int m_seDamage;	// �U�����󂯂��Ƃ���SE

	bool m_isDeath;	// ���S�t���O
	bool m_finish;	// �̗͂�0�ɂȂ������ǂ���

	Camera* m_camNode;
	CollisionStage* m_collisionStage;

	Inventory* m_inventory;
	EnhanceType* m_enhanceType;
	ItemFactory* m_itemFactory;

	Vector3 m_playerPastPos;
	Vector3 m_playerRotate;
	Vector3 m_moveDirection;

	// �A�j���[�V�����؂�ւ��p
	Anim m_nowAnim;
	Anim m_nextAnim;

	bool m_moving;	// �ړ��A�j���[�V�������Đ�����
	float m_elapsedTime;	// �o�ߎ��ԕێ�
	float m_fallTime;		// ���R����������������p

	// �v���C���[�̗̑͂Ɋւ���ϐ�
	int m_hp;	// �v���C���[�̗̑�

	float m_stamina;	// �v���C���[�̌��݂̃X�^�~�i	
	bool m_isDash;		// �����Ă��邩
	float m_duration;	// ���Ԍo�߂��J�E���g����p
	float m_staminaRecovery;	// �X�^�~�i�̉񕜗�
	float m_staminaDecrease;	// �X�^�~�i�̏����

	// �v���C���[�̃W�����v����
	void Jumping();		// �����ŃW�����v���鏈��

	// ---- SE ----
	int m_seWalk;
	int m_seRun;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;
	virtual void OnCollision(const Actor3D* other) override;

public:
	LoadPlayer(
		CollisionStage* collisionStage, 
		Inventory* inventory, 
		EnhanceType* enhanceType,
		const Vector3& pos,
		ItemFactory* itemFactory
	);

	// �A�j���[�V������؂�ւ���(Lerp)
	void ChangeAnimLerp();

	// �A�j���[�V������؂�ւ���(����)
	void ChangeAnimQuick(const Anim nextAnim);

	// �A�j���[�V�������Đ�����
	void PlayAnim();

	// �v���C���[�̒ʏ�ړ�
	void NormalMove();

	// �ړ�������߂�
	void CheckMove();


	// ���������������v�Z����
	void CountFallHeight();

	// �v���C���[�̗̑͂����炷����
	void DecreaseHP(int damage);

	//���Ԓ�~
	void TheWorld();

	bool IsJump()
	{
		return m_isJump;
	}

	// ���Ԃ��~�܂��Ă��邩
	bool IsTheWorld()
	{
		return m_isStop;
	}

	// �N�[���_�E������
	bool IsCoolDown()
	{
		return m_isCooldown;
	}

	// ��~�ł��鎞�Ԃ��擾
	float GetStopTime()
	{
		return m_stopTime;
	}

	// ���݂�Hp�̊�����Ԃ�
	float GetHpRatio()
	{
		return static_cast<float>(m_hp) / static_cast<float>(MaxHp);
	}

	float GetTheWorldTime()
	{
		return m_stopTime;
	}

	float SetTheWorldTime(float theWorldTime)
	{
		m_stopTime = theWorldTime;
	}

	bool GetIsGetting()
	{
		return m_isGetting;
	}

	void GetEnd()
	{
		m_isGetting = false;
	}

	// ���S�t���O���擾
	bool GetIsDeath()
	{
		return m_isDeath;
	}

	// �X�^�~�i�Ǘ�
	void StaminaManagement();

	// ���݂̃X�^�~�i���擾
	float GetStamina()
	{
		return m_stamina;
	}

	// �X�^�~�i�̍ő�l���擾
	float GetMaxStamina()
	{
		return MaxStamina;
	}

	// �̗͂�0�ɂȂ�����
	bool IsFinsh()
	{
		return m_finish;
	}

	//�A�C�e���𗎂Ƃ�����
	void DropItem();
};