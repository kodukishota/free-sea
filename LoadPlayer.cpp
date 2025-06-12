#include"LoadPlayer.h"
#include"Time.h"
#include"Math.h"
#include"Camera.h"
#include"Animation3D.h"
#include"Input.h"
#include"Lerp.h"
#include"Quaternion.h"
#include"CollisionStage.h"
#include"BoxCollider3D.h"
#include<math.h>

// �A�j���[�V�������X�g
const char* LoadPlayer::AnimList[AnimNum] =
{
	"Man/Idle_stand.mv1",
	"Man/Walking.mv1",
	"Man/Sprint.mv1",
	"Man/Die.mv1",
};

LoadPlayer::LoadPlayer(
	CollisionStage* collisionStage,
	const Vector3& pos
) :
	Actor3D("Player", pos),
	m_model(MV1LoadModel("Resource/Man/Man.mv1")),
	m_animIndex(0),
	m_moving(false),
	m_nowAnim(Anim::Idle),
	m_nextAnim(Anim::Idle),
	m_moveDirection(Vector3(0, 0, 0)),
	m_camNode(nullptr),
	m_collisionStage(collisionStage),
	m_elapsedTime(0),
	m_fallTime(0),
	m_isJump(false),
	m_isJumping(false),
	m_isFloating(false),
	m_duration(0),
	m_isFall(false),
	m_fallStartY(0),
	m_isDeath(false),
	m_isDash(false),
	m_stamina(MaxStamina),
	m_staminaRecovery(0),
	m_staminaDecrease(0),
	m_runSpeed(RunSpeed),
	m_finish(false),
	m_cutTree(false),
	m_fellDown(false),
	m_bodyTemperature(MaxBodyTemperature),
	m_downTemperature(FirstDownTemperature),
	m_downTemperatureCoolDown(0),
	m_isMenu(false),
	m_hungerLevel(FullStomach),
	m_isWarmthFlag(false),
	m_warmthTemperatureCoolDown(0),
	m_hungerTime(0)
{
	//-----�A�j���[�V�����̍쐬-----
	// �A�j���[�V�����N���X�����X�g������
	for (int i = 0; i < AnimNum; i++)
	{
		if (i < AnimNum - 1)
		{
			m_attachAnimList.push_back(new Animation3D(m_model, AnimList[i]));
			AddChild(m_attachAnimList[i]);
		}
		else
		{
			// ���[�v���Ȃ��A�j���[�V����
			m_attachAnimList.push_back(new Animation3D(m_model, AnimList[i], false));
			AddChild(m_attachAnimList[i]);
		}
	}

	// �A�j���[�V�����p�̈ʒu
	m_playerPastPos = m_transform.position;

	// �v���C���[�̉�](x, y, z)
	m_playerRotate = Vector3(0, 0, 0);
	m_transform.angle = Vector3(0, 180, 0);

	// �J�����̐���
	m_camNode = new Camera(this, collisionStage);
	AddChild(m_camNode);

	// �ŏ��̃A�j���[�V�������w��
	m_attachAnimList[static_cast<int>(Anim::Idle)]->FadeIn();

	m_collider = new BoxCollider3D(ColSize, ColOffset);

	// �̗͂̏����l��ݒ�
	m_hp = MaxHp;

	// ���𕷂��|�C���g���X�V
	Set3DSoundListenerPosAndFrontPos_UpVecY(this->GetPosition(), m_camNode->CamFrontPlaneVec());
}

void LoadPlayer::Load()
{
	// �_���[�W�{�C�X��ݒ�
	m_seDamage = LoadSoundMem("Resource/sound/damage.mp3");
	ChangeVolumeSoundMem(128, m_seDamage);

	// ���鉹
	m_seRun = LoadSoundMem("Resource/sound/player_run.mp3");

	// ������
	m_seWalk = LoadSoundMem("Resource/sound/player_walk.mp3");

	Actor3D::Load();
}

void LoadPlayer::Release()
{
	// se���폜
	DeleteSoundMem(m_seDamage);
	DeleteSoundMem(m_seRun);
	DeleteSoundMem(m_seWalk);
	// �v���C���[�̃��f�����폜
	MV1DeleteModel(m_model);

	Actor3D::Release();
}

// �A�j���[�V������؂�ւ���(Lerp)
void LoadPlayer::ChangeAnimLerp()
{
	if (m_nowAnim == m_nextAnim) return;

	m_attachAnimList[static_cast<int>(m_nowAnim)]->FadeOut();
	m_attachAnimList[static_cast<int>(m_nextAnim)]->FadeIn();

	m_nowAnim = m_nextAnim;
}

// �A�j���[�V������؂�ւ���(����)
void LoadPlayer::ChangeAnimQuick(const Anim nextAnim)
{
	m_attachAnimList[static_cast<int>(m_nowAnim)]->ChangeOut();
	m_attachAnimList[static_cast<int>(nextAnim)]->ChangeIn();

	m_nowAnim = nextAnim;
	m_nextAnim = nextAnim;
}

// �A�j���[�V�������Đ�����
void LoadPlayer::PlayAnim()
{
	// �J�����̈ʒu�ƌ���
	m_camNode->SetCamPosAndTag();

	// ���f���̉�]
	Quaternion::RotateAxisY(m_model, m_transform.angle.y, m_transform.position);

	// ���f���̕`��
	MV1DrawModel(m_model);
	
#ifdef _DEBUG
	DrawFormatString(0, 160, GetColor(255, 255, 255),
		"PlayerPos Vector3(%.0f, %.0f, %.0f)",
		m_transform.position.x, m_transform.position.y, m_transform.position.z
	);

	DrawFormatString(0, 150, GetColor(255, 255, 255), "PlayerHP %d", m_hp);
#endif // _DEBUG
}

//�A�b�v�f�[�g�֐�
void LoadPlayer::Update()
{
#ifdef _DEBUG
	// press "r" => ���X�^�[�g
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_R))
	{
		m_transform.position = SpawnPos;
		m_hp = MaxHp;
	}

	// press "0" => ���E
	if (Input::GetInstance()->IsKeyDown(KEY_INPUT_0))
	{
		m_hp = 0;
	}
#endif // _DEBUG

	if (m_hp <= 0)
	{
		if(!m_finish) m_finish = true;

		if (m_nowAnim != Anim::Death)
		{
			// ���S�A�j���[�V�������Đ�
			ChangeAnimQuick(Anim::Death);
			m_camNode->ModeChange();
		}

		if (m_attachAnimList[static_cast<int>(m_nowAnim)]->FinishAnim())
		{
			// ���S�A�j���[�V�������I�������玀�S�t���O�𗧂Ă�
			m_isDeath = true;
		}
	}
	else
	{
		if (!m_nowTrede && !m_isMenu)
		{
			NormalMove();
		}

		if (m_fellDown)
		{
			m_cutTree = false;
			m_fellDown = true;
		}
	}

	DownBodyTemperature();
	DownHungerLevel();

	// �A�j���[�V�����̐؂�ւ�
	ChangeAnimLerp();

	// 1�t���[���O�̈ʒu���X�V
	m_playerPastPos = m_transform.position;

	// ���𕷂��|�C���g���X�V
	Set3DSoundListenerPosAndFrontPos_UpVecY(this->GetPosition(), m_camNode->CamFrontPlaneVec());
}

// �W�����v����
void LoadPlayer::Jumping()
{
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();

	m_transform.position.y += JumpPower - Gravity * m_elapsedTime;

	// ���������ɐG�ꂽ��
	if (m_isJumping && m_collisionStage->GetHeight(m_transform.position).HitFlag)
	{
		m_isJump = false;
		m_isJumping = false;

		CountFallHeight();
	}
	else
	{
		m_isJumping = true;
	}
}

// �v���C���[�̒ʏ�ړ�
void LoadPlayer::NormalMove()
{
	// ----�v���C���[�̈ړ�----
	float inputX = 0;
	float inputZ = 0;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_S)) inputZ = -1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_W)) inputZ = 1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_A)) inputX = -1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_D)) inputX = 1;

	// �ړ�����������i�d�͂ɉ����č��E�ړ��̌������ς��j
	m_moveDirection = m_camNode->CamFrontPlaneVec() * inputZ + m_camNode->CamRight() * inputX;

	// �d�͂����Z�i�W�����v���łȂ� && ���n���Ă��Ȃ��Ƃ��̂݁j
	if (!m_isJump && m_collisionStage->GetHeight(m_transform.position).HitFlag == 0)
	{
		m_fallTime += Time::GetInstance()->GetDeltaTime();
		// �ʏ펞
		m_transform.position.y -= Gravity * m_fallTime;

		if (!m_isFall)
		{
			// �����J�n���̍�����ێ�
			m_fallStartY = m_transform.position.y;
			m_isFall = true;
		}
	}
	else if (m_collisionStage->GetHeight(m_transform.position).HitFlag == 1)
	{
		// �v���C���[�̍����𑫏�̍����ɍ��킹��
		m_fallTime = 0;
		// �ʏ펞
		m_transform.position.y = m_collisionStage->GetHeight(m_transform.position).HitPosition.y;

		if (m_isFall)
		{
			CountFallHeight();
			m_isFall = false;
		}
	}

	// ���ۂ̈ړ�������߂�
	CheckMove();

	// �X�^�~�i�Ǘ�
	StaminaManagement();

	// �i�ޗ\���ɑ��ꂪ���邩
	if (!m_collisionStage->CheckStage(this->GetPosition()))
	{
		// �Ȃ��Ƃ�
		m_transform.position.x = m_playerPastPos.x;
		m_transform.position.z = m_playerPastPos.z;
	}

	// �W�����v
	if (!m_isJump && m_collisionStage->GetHeight(m_transform.position).HitFlag != 0 && Input::GetInstance()->IsKeyDown(KEY_INPUT_SPACE))
	{
		m_isJump = true;
		m_elapsedTime = 0;
		// �W�����v�̃X�^�[�g�n�_���L�^
		m_fallStartY = m_transform.position.y;
	}
	else if (m_isJump)
	{
		Jumping();
	}

	// �v���C���[�̉�]�Ō��݂̌����Ɖ�]�\��̌����̕������Ⴄ�Ƃ��ɕ��������킹��i180 �` -180�ł������Ȃ����߁j
	if (!m_moveDirection.IsZero())
	{
		float afterAngle = 0;

		Math::MatchAngleSign(afterAngle, m_moveDirection, m_transform.angle);

		m_transform.angle.y = Lerp::Exec(m_transform.angle.y, afterAngle, 0.2f);
	}

	// ---- �ړ��A�j���[�V���� ----
	if (m_collisionStage->GetHeight(m_transform.position).HitFlag != 0)
	{
		if (!m_isJump)
		{
			if (m_playerPastPos.x != m_transform.position.x ||
				m_playerPastPos.z != m_transform.position.z)
			{
				if (!Input::GetInstance()->IsKeyPress(KEY_INPUT_LSHIFT))
				{
					// walk
					m_nextAnim = Anim::Walk;
					m_moving = true;
				}
				else
				{
					// run
					m_nextAnim = Anim::Run;
					m_moving = true;
				}
			}
			else
			{
				// idle
				m_nextAnim = Anim::Idle;
				m_moving = false;
			}
		}
	}
}

// �ړ�������߂�
void LoadPlayer::CheckMove()
{
	// �ړ�
	if (m_stamina > 0)
	{

		// �_�b�V���t���O�̊Ǘ�
		m_isDash = Input::GetInstance()->IsKeyPress(KEY_INPUT_LSHIFT);
		
		if (m_moveDirection.IsZero())
		{
			m_isDash = false;
		}

		Vector3 nextPos = m_transform.position + m_moveDirection * (Input::GetInstance()->IsKeyPress(KEY_INPUT_LSHIFT) ? m_runSpeed : WalkSpeed);

		// �����ǂɓ������Ă�����
		if (m_collisionStage->CapsuleCollider(nextPos) != 0)
		{
			// �ړ��ł�������𒲐�
			Vector3 dir = Vector3(0, 0, 0);

			// �ǂ̕��������i�߂Ȃ��悤�ɂ���
			for (int i = 0; i < m_collisionStage->CapsuleCollider(nextPos); i++)
			{
				// ���������|���S����������
				Vector3 hitPos = m_collisionStage->GetColSphere().Dim[i].HitPosition;
				Vector3 wallDir = Math::Normalized(this->GetPosition() - hitPos);

				if (std::abs(dir.x) < std::abs(wallDir.x))
				{
					dir.x = wallDir.x;
				}
				if (std::abs(dir.z) < std::abs(wallDir.z))
				{
					dir.z = wallDir.z;
				}
			}

			m_moveDirection.x = dir.x - m_moveDirection.x;
			m_moveDirection.z = dir.z - m_moveDirection.z;
		}

		m_transform.position += m_moveDirection * (Input::GetInstance()->IsKeyPress(KEY_INPUT_LSHIFT) ? m_runSpeed : WalkSpeed);

		if (!m_moveDirection.IsZero())
		{
			if (m_isDash)
			{
				if (CheckSoundMem(m_seRun) == 0)
				{
					// �ړ����x�ɉ�����se��ς���
					if (CheckSoundMem(m_seWalk) == 1)
					{
						StopSoundMem(m_seWalk);
					}
					PlaySoundMem(m_seRun, DX_PLAYTYPE_BACK);
				}
			}
			else
			{
				if (CheckSoundMem(m_seWalk) == 0)
				{
					// �ړ����x�ɉ�����se��ς���
					if (CheckSoundMem(m_seRun) == 1)
					{
						StopSoundMem(m_seRun);
					}
					PlaySoundMem(m_seWalk, DX_PLAYTYPE_BACK);
				}
			}
		}
		else
		{
			// �ړ��I������SE���~�߂�
			if (CheckSoundMem(m_seRun) == 1)
			{
				StopSoundMem(m_seRun);
			}
			if (CheckSoundMem(m_seWalk) == 1)
			{
				StopSoundMem(m_seWalk);
			}
		}
	}
	else
	{
		// �X�^�~�i���Ȃ��Ȃ������_�ő���pSE���~�߂�
		if (CheckSoundMem(m_seRun) == 1)
		{
			StopSoundMem(m_seRun);
		}

		Vector3 nextPos = m_transform.position + m_moveDirection * WalkSpeed;
		m_isDash = false;

		// �i�ޗ\���ɕǂ���������
		// �����ǂɓ������Ă�����
		if (m_collisionStage->CapsuleCollider(nextPos) != 0)
		{
			// �ړ��ł�������𒲐�
			Vector3 dir = Vector3(0, 0, 0);

			// �ǂ̕��������i�߂Ȃ��悤�ɂ���
			for (int i = 0; i < m_collisionStage->CapsuleCollider(nextPos); i++)
			{
				// ���������|���S����������
				Vector3 hitPos = m_collisionStage->GetColSphere().Dim[i].HitPosition;
				Vector3 wallDir = Math::Normalized(this->GetPosition() - hitPos);

				if (std::abs(dir.x) < std::abs(wallDir.x))
				{
					dir.x = wallDir.x;
				}
				if (std::abs(dir.z) < std::abs(wallDir.z))
				{
					dir.z = wallDir.z;
				}
			}

			m_moveDirection.x = dir.x - m_moveDirection.x;
			m_moveDirection.z = dir.z - m_moveDirection.z;
		}

		m_transform.position += m_moveDirection * WalkSpeed;

		if (!m_moveDirection.IsZero())
		{
			if (CheckSoundMem(m_seWalk) == 0)
			{
				// �ړ����x�ɉ�����se��ς���
				PlaySoundMem(m_seWalk, DX_PLAYTYPE_BACK);
			}
		}
		else
		{
			if (CheckSoundMem(m_seWalk) == 1)
			{
				// �ړ����x�ɉ�����se��ς���
				StopSoundMem(m_seWalk);
			}
		}
	}

}

void LoadPlayer::Draw()
{
	// �A�j���[�V�����Đ�
	PlayAnim();

	DrawFormatString(0, 500, GetColor(255, 255, 255),
		"�̉�%f",
		m_bodyTemperature
	);
}

void LoadPlayer::OnCollision(const Actor3D* other)
{
	if (other->GetName() == "Tree")
	{
		if (Input::GetInstance()->IsKeyPress(KEY_INPUT_F))
		{
			m_cutTree = true;
		}
	}

	if (other->GetName() == "FirePlace")
	{
 		m_isWarmthFlag = true;
	}

	if (other->GetName() == "Treder")
	{
		if (Input::GetInstance()->IsKeyPress(KEY_INPUT_F) && !m_isMenu)
		{
			m_nowTrede = true;
		}
	}
}

// ���������������v�Z����
void LoadPlayer::CountFallHeight()
{
	if ((abs(m_transform.position.y) - abs(m_fallStartY)) >= 1300.0f)
	{
		// �u�]���鍂�����痎�������Ƃ�
		m_hp = 0;
	}
	m_fallStartY = 0;
}

// �v���C���[�̗̑͂����炷����
void LoadPlayer::DecreaseHP(int damage)
{
	m_hp -= damage;

	// SE:��_���[�W
	PlaySoundMem(m_seDamage, DX_PLAYTYPE_BACK);

	if (m_hp <= 0)
	{
		m_hp = 0;
	}
}

//�̉�����
void LoadPlayer::DownBodyTemperature()
{
	//�g�F�̋߂��ɂ���Ƒ̉��͉�����Ȃ�
	if (!m_isWarmthFlag)
	{
		m_downTemperatureCoolDown += Time::GetInstance()->GetDeltaTime();
	}

	//�ܕb�����Ƃɑ̉�������
	if (m_bodyTemperature >= 0 && m_downTemperatureCoolDown >= FirstDownTemperatureTime)
	{
		m_bodyTemperature -= m_downTemperature;
		m_downTemperatureCoolDown = 0;
	}
}

//�̉���
void LoadPlayer::WarmthBodyTemperature()
{
	m_warmthTemperatureCoolDown += Time::GetInstance()->GetDeltaTime();
	
	//�ܕb�����Ƃɑ̉���������
	if (m_warmthTemperatureCoolDown >= FirstDownTemperatureTime &&
		m_bodyTemperature < MaxBodyTemperature)
	{
		m_bodyTemperature += m_downTemperature;
		m_warmthTemperatureCoolDown = 0;
		m_isWarmthFlag = false;
	}
}

void LoadPlayer::DownHungerLevel()
{
	m_hungerTime += Time::GetInstance()->GetDeltaTime();

	//�ܕb�����Ƃɂ��Ȃ�������
	if (m_hungerLevel >= 0 && m_hungerTime >= DownHungerLevelTime)
	{
		m_hungerLevel -= DownHungerLevelValue;
		m_hungerTime = 0;
	}
}

// �X�^�~�i�Ǘ�
void LoadPlayer::StaminaManagement()
{
	if (m_isDash)
	{
		m_staminaDecrease = StaminaDecreaseAmount;

		// �����Ă���Ԃ̓X�^�~�i�����炷
		m_stamina -= m_staminaDecrease * Time::GetInstance()->GetDeltaTime();
		m_duration = 0;
		if (m_stamina <= 0)
		{
			m_stamina = 0;
		}
	}
	else
	{
		m_staminaRecovery = StaminaRecoveryAmount;

		// ���łɃX�^�~�i���ő�̎�
		if (m_stamina == MaxStamina) return;

		// �����Ă��Ȃ��Ƃ�
		m_duration += Time::GetInstance()->GetDeltaTime();

		if (m_duration >= TimeToRecoverStamina)
		{
			// �X�^�~�i�񕜂܂ł̎��Ԃ𒴂�����񕜂��n�߂�
			m_stamina += m_staminaRecovery * Time::GetInstance()->GetDeltaTime();
		}

		if (m_stamina >= MaxStamina)
		{
			// �X�^�~�i�̍ő�l�𒴂����璲��
			m_stamina = MaxStamina;
			m_duration = 0;
		}
	}
}