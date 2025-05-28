#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"Sprite.h"

class LoadPlayer;
class Camera;

class Ax : public Actor3D
{
private:
	static constexpr int GoodHandleUiPosIndex = 9;
	//�O�b�h�̈ʒu
	static constexpr int GoodHandleUiPosX[GoodHandleUiPosIndex] = {420,495,570,645,720,795,870,945,1020 };
	static constexpr Vector2 SkillCheckUiPos = Vector2(720, 750);
	static constexpr Vector3 OffSet = Vector3(50,50,-30);
	static constexpr float HandleSpeed = 5;				//�n���h���������X�s�[�h
	static constexpr int FristDurabilityValue = 100;	//�ϋv��
	static constexpr int AttackDamage = 10;				//�U����
	static constexpr int GoodHandleSize = 150;		//�O�b�h�̉摜���T�C�Y
	static constexpr int PerfectHandleSize = 30;	//�p�[�t�F�N�g�̉摜���T�C�Y

	static constexpr int ConsumptionDurability = 5;	//���Ցϋv�l

	int m_model;

	int m_durabilityValue;
	int m_attackDamage;
	int m_consumptionDurability;

	bool m_isCutTreeFlag;	//�؂𔰂�����

	Sprite m_skillCheckUi;				//�X�L���`�F�b�N�̃o�[
	Sprite m_skillCheckHandleUi;		
	Sprite m_checkGoodHandleUi;			//
	Sprite m_checkPerfectHandleUi;		//

	Transform m_skillCheckUiPos;		//�X�L���`�F�b�N�̃o�[�̈ʒu
	Transform m_skillCheckHandleUiPos;	//
	Transform m_checkGoodHandleUiPos;	//
	Transform m_checkPerfectHandleUiPos;	//

	LoadPlayer* m_player;
	Camera* m_camera;

	bool m_turnHandleRight;		//�n���h�����E�ɍs���ׂ���
	bool m_turnHandleLeft;		//�n���h�������ɍs���ׂ���
	bool m_positionDecision;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;

public:
	Ax( LoadPlayer* player, Camera* camera);

	//�؂𔰂�
	void CutTree();

	int GetCutDamage()
	{
		return m_attackDamage;
	}

	bool GetIsCutTree()
	{
		return m_isCutTreeFlag;
	}

	void OffIsCutTree()
	{
		m_isCutTreeFlag = false;
	}
};