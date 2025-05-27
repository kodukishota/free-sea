#include "Enemy.h"
#include "Time.h"
#include "Math.h"
#include "Animation3D.h"
#include "Collision3D.h"
#include"ActorCollision3D.h"
#include"BoxCollider3D.h"
#include"LoadPlayer.h"
#include"CheckRoot.h"
#include"Quaternion.h"
#include"Audio3D.h"
#include"NavMesh.h"
#include "Input.h"
#include "Lerp.h"
#include<future>
#include <math.h>

// �A�j���[�V�������X�g
const char* Enemy::AnimList[AnimNum] =
{
	"Zombie/ZombieIdle.mv1",
	"Zombie/ZombieWalk.mv1",
	"Zombie/ZombieAttack.mv1",
};

Enemy::Enemy(NavMesh* navMesh, const Vector3& pos, LoadPlayer* loadPlayer) :
	Actor3D("Enemy", pos),
	m_model(MV1LoadModel("Resource/Zombie/Zombie.mv1")),
	m_player(loadPlayer),
	m_animIndex(0),
	m_nowAnim(Anim::Idle),
	m_nextAnim(Anim::Idle),
	m_navMesh(navMesh),
	m_moveDirection(Vector3(0,0,0)),
	m_isSet(false),
	m_isFind(false),
	m_isAttack(false),
	m_countCoolTime(false),
	m_durationCoolTime(0),
	m_isMove(false),
	m_polyCount(0),
	m_isCheck(false),
	m_pastAttackFlg(false),
	m_stoped(false)
{
	// �A�j���[�V�����N���X�����X�g������
	for (int i = 0; i < AnimNum; i++)
	{
		if (i < AnimNum - 1)
		{
			// ���[�v����A�j���[�V����
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

	// �G�̉�
	AddChild(new Audio3D("Resource/sound/zombie_voice.mp3", this));

	// ���f�����w��ꏊ�ɕ`��
	MV1SetPosition(m_model, pos);

	// �A�j���[�V�����p�̈ʒu
	m_enemyPastPos = m_enemyPos;

	// �ŏ��̃A�j���[�V�������w��
	m_attachAnimList[static_cast<int>(Anim::Idle)]->FadeIn();

	m_collider = new BoxCollider3D(FindColSize, ColOffset);

	m_checkRoot = new CheckRoot(m_navMesh);
}

// �A�j���[�V������؂�ւ���(Lerp)
void Enemy::ChangeAnimLerp()
{
	if (m_nowAnim == m_nextAnim) return;

	m_attachAnimList[static_cast<int>(m_nowAnim)]->FadeOut();
	m_attachAnimList[static_cast<int>(m_nextAnim)]->FadeIn();

	m_nowAnim = m_nextAnim;
	
}

// �A�j���[�V������؂�ւ���(����)
void Enemy::ChangeAnimQuick(const Anim nextAnim)
{
	m_attachAnimList[static_cast<int>(m_nowAnim)]->ChangeOut();
	m_attachAnimList[static_cast<int>(nextAnim)]->ChangeIn();

	m_nowAnim = nextAnim;
	m_nextAnim = nextAnim;
	
}

// �A�j���[�V�������Đ�����
void Enemy::PlayAnim()
{
	// ���f���̕`��
	MV1DrawModel(m_model);
#ifdef _DEBUG
	DrawFormatString(0, 60, GetColor(255, 255, 255),
		"EnemyPos Vector3(%.0f, %.0f, %.0f)",
		m_enemyPos.x, m_enemyPos.y, m_enemyPos.z
	);
#endif // _DEBUG

}

void Enemy::Update()
{
	if (m_player->IsTheWorld())
	{
		if (!m_stoped)
		{
			m_stoped = m_player->IsTheWorld();
			m_attachAnimList[static_cast<int>(m_nowAnim)]->StopAnim();
		}
		return;
	}
	else
	{
		if (m_stoped != m_player->IsTheWorld())
		{
			m_stoped = m_player->IsTheWorld();
			m_attachAnimList[static_cast<int>(m_nowAnim)]->StartAnim();
		}	
	}
		
	if (m_isAttack)
	{
		Attack();
	}
	else
	{
		// �U�����łȂ��Ƃ�
		if (m_isFind)
		{
			MoveCombat();
			// �A�j���[�V�����͏�Ɉړ��A�j���[�V����
			m_nextAnim = Anim::Run;
		}
		else
		{
			MoveWanderAround();
		}
		// ���݂̈ړ��������擾
		m_moveDirection = m_transform.position - m_enemyPastPos;
	}
	
	// ���f���̉�]
	if (!m_moveDirection.IsZero())
	{
		float afterAngle = 0;

		Math::MatchAngleSign(afterAngle, m_moveDirection, m_transform.angle);

		m_transform.angle.y = Lerp::Exec(m_transform.angle.y, afterAngle, 0.2f);
	}

	// �A�j���[�V�����̐؂�ւ�
	ChangeAnimLerp();

	m_enemyPastPos = this->GetPosition();

	m_pastAttackFlg = m_isAttack;
}

// �G�̈ړ��i�Ր�Ԑ��j
void Enemy::MoveCombat()
{
	if (!m_isCheck)
	{
		if (!m_found)
		{
			m_thread = new std::thread(&CheckRoot::SetPathPlan, m_checkRoot, this->GetPosition(), m_player->GetPosition(), &m_polyCount, &m_found);
			m_thread->detach();
		}
		else
		{
			// �ړ�����
			m_checkRoot->MoveInitialize(this->GetPosition());
			m_isCheck = true;
			m_found = false;

			// thread�̔j��
			delete m_thread;
			m_thread = nullptr;
		}
	}
	else
	{
		m_transform.position = m_checkRoot->Move(this->GetPosition(), MoveSpeedCombat, Width, &m_polyCount);

		// ������x�ړ����ł����� || �v���C���[�ɍU�������� || �v���C���[�Ɠ����|���S���ɏ������@�ĒT��
		if (m_polyCount <= 0 || 
			m_pastAttackFlg != m_isAttack ||
			m_checkRoot->CheckPlayerPoly(this->GetPosition(), m_player->GetPosition())
			)
		{
			// ����̒T�������폜
			m_checkRoot->RemovePathPlan();
			m_isCheck = false;
		}
	}
}

// �G�̈ړ��i�p�j�j
void Enemy::MoveWanderAround()
{
	if (!m_isMove)
	{
		if (!m_found)
		{
			m_thread = new std::thread(&CheckRoot::SetPathPlan, m_checkRoot, this->GetPosition(), m_navMesh->GetPos(), &m_polyCount, &m_found);
			m_thread->detach();
		}
		else
		{
			// �ړ�����
			m_checkRoot->MoveInitialize(this->GetPosition());
			m_isMove = true;
			m_found = false;

			// thread�̔j��
			delete m_thread;
			m_thread = nullptr;
		}
	}
	else
	{
		if (m_transform.position != m_checkRoot->Move(this->GetPosition(), MoveSpeed, Width, &m_polyCount))
		{
			// �ړI�n�ɓ������Ă��Ȃ��Ƃ�
			m_transform.position = m_checkRoot->Move(this->GetPosition(), MoveSpeed, Width, &m_polyCount);
		}
		else
		{
			// �ړI�ɓ��� => ����̒T�����ʂ�j�� && �ēx�ړI�n�̐ݒ�ƌo�H�T��
			m_checkRoot->RemovePathPlan();
 			m_isMove = false;
		}

		// �A�j���[�V����
		if (this->GetPosition() != m_enemyPastPos)
		{
			m_nextAnim = Anim::Run;
		}
		else
		{
			m_nextAnim = Anim::Idle;
		}
	}
	
}

void Enemy::Draw()
{
	if (!m_player->IsTheWorld())
	{
		// �A�j���[�V�����Đ�
		PlayAnim();

		Quaternion::RotateAxisY(m_model, m_transform.angle.y, m_transform.position);
	}

	// ���f���̕`��
	MV1DrawModel(m_model);

#ifdef _DEBUG
	DrawFormatString(0, 40, GetColor(255, 255, 255),
		"EnemyPos Vector3(%.0f, %.0f, %.0f)",
		this->GetPosition().x, this->GetPosition().y, this->GetPosition().z
	);
#endif // DEBUG
}

void Enemy::OnCollision(const Actor3D* other)
{
	if (other->GetName() == "Player" && !m_player->IsTheWorld())
	{
		if (!m_isFind)
		{
			// �v���C���[�������Ă��Ȃ� => �R���C�_�[������������
			m_collider->ChangeSize(AttackColSize);
			m_isFind = true;

			// �v���C���[���ĒT��
			delete m_thread;
			m_thread = nullptr;
			m_checkRoot->RemovePathPlan();
			m_found = false;
		}
		else
		{
			if (m_isAttack) return;
			// �v���C���[�𔭌��ς� => �U��
			m_nextAnim = Anim::Attack;
			m_player->DecreaseHP(Power);
			m_isAttack = true;
		}
	}
}

// �G�̍U��
void Enemy::Attack()
{
	// �U�����͓����Ȃ�
	if (m_attachAnimList[static_cast<int>(m_nowAnim)]->FinishAnim())
	{
		// �U���A�j���[�V�����̏I���Ɠ����ɃA�j���[�V�����ύX
		ChangeAnimQuick(Anim::Idle);
		m_countCoolTime = true;
	}

	if (m_countCoolTime)
	{
		m_durationCoolTime += Time::GetInstance()->GetDeltaTime();

		// �N�[���^�C���I��
		if (m_durationCoolTime <= CoolTime)
		{
			m_countCoolTime = false;
			m_durationCoolTime = 0;
			m_isAttack = false;
		}
	}
}

// ���\�[�X�̉��
void Enemy::Release()
{
	// ���f�����폜
	MV1DeleteModel(m_model);

	// thread��j��
	delete m_thread;
	m_thread = nullptr;

	// ���Ƃ��Ƃ�release�����s
	Actor3D::Release();
}