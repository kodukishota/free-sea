#pragma once
#include <list>

class Actor;

// Actor���m�̏Փ˔���N���X
class ActorCollision
{
private:
	std::list<Actor*> m_actorList;	// �Փ˔��������Actor�̃��X�g

	// �R���X�g���N�^
	ActorCollision() {}

public:
	// �V���O���g��
	static ActorCollision* GetInstance()
	{
		static ActorCollision instance;
		return &instance;
	}

	// �o�^
	void Register(Actor* actor)
	{
		m_actorList.push_back(actor);
	}

	// �폜
	void Remove(Actor* actor)
	{
		m_actorList.remove(actor);
	}

	// �X�V
	void Update();

#ifdef _DEBUG
	// �`��
	void Draw() const;
#endif
};
