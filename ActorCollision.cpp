#include "ActorCollision.h"
#include "Actor.h"
#include "Collider.h"

#include "BoxCollider2D.h"

// �X�V
void ActorCollision::Update()
{
	// �r���Ń��X�g�ւ̒ǉ���폜���������Ă������悤�ɁA�R�s�[�ŉ�
	std::list<Actor*> actorList(m_actorList);

	// ��������ŏՓ˔���
	for (auto it1 = actorList.begin(); it1 != actorList.end(); it1++)
	{
		for (auto it2 = it1; it2 != actorList.end(); it2++)
		{
			// �C�e���[�^����Actor*�����o��
			Actor* actor1 = *it1;
			Actor* actor2 = *it2;

			// �Փ˔���̌`�󂪖���������X�L�b�v
			if (!actor1->GetCollider()) continue;
			if (!actor2->GetCollider()) continue;

			// �������g�̓X�L�b�v
			if (actor1 == actor2) continue;

			// �Փ˔���
			if (actor1->GetCollider()->CheckCollision(
				actor1->GetTransform(),
				actor2->GetTransform(), actor2->GetCollider() ))
			{
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);
			}
			/*
			const BoxCollider2D* box = dynamic_cast<const BoxCollider2D*>(actor1->GetCollider());
			if (box != nullptr)
			{
				// Collider*�͖{����BoxCollider*������
			}
			else
			{
				// Collider*��BoxCollider*�ł͂Ȃ�����
			}
			*/
		}
	}
}

#ifdef _DEBUG
void ActorCollision::Draw() const
{
	for (auto actor : m_actorList)
	{
		actor->GetCollider()->Draw(actor->GetTransform());
	}
}
#endif
