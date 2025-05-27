#pragma once
#include"Actor3D.h"
#include"Vector3.h"

class LoadPlayer;
class CollisionStage;

class Camera : public Actor3D
{
public:
	enum SightMode
	{
		First,
		Third,
	};

private:
	static constexpr Vector3 StartPos = Vector3(1300, 250, 300);
	static constexpr float DiffY = 150;
	static constexpr float CamDiff = 400.0f;	// �v���C���[�ƃJ�����̋���
	static constexpr float DiffTagY = 200.0f;	// ����������̍���
	static constexpr float AddAngleY = 2.0f;	// y���̍��������Z���Ă������߂̒l
	static constexpr float DecMouseDiff = 10;	// �}�E�X�̈ړ��ʂ���]�Ɏg�����߂ɁA�l�����������銄��
	static constexpr float CamRot = 720.0f;	// �}�E�X�̈ړ��ʂɑ΂���J�����̉�]�̕���
	static constexpr float CamNearDist = 10.0f;	// �J�����ɉf��ł��߂�����
	static constexpr float CamFarDist = 20000.0f;// �J�����ɉf��ł���������
	// �P�l�̗p
	static constexpr float MaxCamHeight = 500.0f;	// �J�����̒����_�̍ő�̍�������
	static constexpr float MinCamHeight = -100.0f;	// �J�����̒����_�̍Œ�̍�������

	Vector3 m_camTarget;
	Vector3 m_pastPlayerPos;

	LoadPlayer* m_loadPlayerNode;
	CollisionStage* m_collisionStage;
	bool m_pastTerning;		// 1�t���[���O�̏d�͂̌���
	float m_diffY;		// �J�����p�x���������ς���悤
	SightMode m_sightMode;	// ���̎��_���[�h

	bool m_isLocked;
	bool m_isChange;	// �J�����̃��[�h�؂�ւ�����

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:
	Camera(LoadPlayer* player, CollisionStage* collisionStage);

	// �J�����̏ꏊ�Əœ_��ݒ�
	void SetCamPosAndTag();

	// �J�����̐��ʃx�N�g�����擾����(XYZ)
	Vector3 CamFrontVec();

	// �J�����̐��ʃx�N�g�����擾(XZ����)
	Vector3 CamFrontPlaneVec();

	// �J�����̉E�����x�N�g�����擾
	Vector3 CamRight();

	// �J�����𓮂���
	void MoveCam(const Vector3& playerPos);

	// 3�l�̎��_
	void ThirdPerson(const Vector3& playerPos);

	// 1�l�̎��_
	void FirstPerson(const Vector3& playerPos);

	// �J�����̃��[�h��ς���
	void ChangeSightMode(const Vector3& playerPos);

	// �J�����̃��[�h��؂�ւ���\��
	void ModeChange()
	{
		m_isChange = true;
	}

	// �J�����̕`�拗���𒲐�
	void SetCamClipRange();
};