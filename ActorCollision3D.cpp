#include "ActorCollision3D.h"
#include "Actor3D.h"
#include "Collider3D.h"

#include "BoxCollider3D.h"

// �X�V
void ActorCollision3D::Update()
{
	// �r���Ń��X�g�ւ̒ǉ���폜���������Ă������悤�ɁA�R�s�[�ŉ�
	std::list<Actor3D*> actorList(m_actorList);

	// ��������ŏՓ˔���
	for (auto it1 = actorList.begin(); it1 != actorList.end(); it1++)
	{
		for (auto it2 = it1; it2 != actorList.end(); it2++)
		{
			// �C�e���[�^����Actor*�����o��
			Actor3D* actor1 = *it1;
			Actor3D* actor2 = *it2;

			// �Փ˔���̌`�󂪖���������X�L�b�v
			if (!actor1->GetCollider()) continue;
			if (!actor2->GetCollider()) continue;

			// �������g�̓X�L�b�v
			if (actor1 == actor2) continue;

			// �Փ˔���
			if (actor1->GetCollider()->CheckCollision(
				actor1->GetTransform(),
				actor2->GetTransform(), actor2->GetCollider()))
			{
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);
			}
		}
	}
}

#ifdef _DEBUG
void ActorCollision3D::Draw() const
{
	for (auto actor : m_actorList)
	{
		actor->GetCollider()->Draw(actor->GetTransform());
	}
}
#endif
