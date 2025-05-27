#pragma once
#include <list>

class Actor3D;

// Actor3D���m�̏Փ˔���N���X
class ActorCollision3D
{
private:
	std::list<Actor3D*> m_actorList;	// �Փ˔��������Actor�̃��X�g

	// �R���X�g���N�^
	ActorCollision3D() {}

public:
	// �V���O���g��
	static ActorCollision3D* GetInstance()
	{
		static ActorCollision3D instance;
		return &instance;
	}

	// �o�^
	void Register(Actor3D* actor)
	{
		m_actorList.push_back(actor);
	}

	// �폜
	void Remove(Actor3D* actor)
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
