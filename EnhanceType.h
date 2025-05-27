#pragma once
#include "Inventory.h"

class Inventory;

class EnhanceType
{
private:
	bool m_onInventoryButton;
	bool m_onHaveWeightButton;
	bool m_onTheWorldTimeButton;
	bool m_onUseTheWorldButton;
	bool m_onStaminaRecoveryButton;
	bool m_onStaminaDecreaseButton;

	int m_maxHaveInventory;	//�C���x���g���̍ő�e��
	int m_maxHaveWeight;		//���Ă�ő�e��

	float m_maxTheWorldTime;	//�����~�߂��ő厞��
	int m_maxUseTheWorld;	//�����~�߂��ő��

	float m_staminaRecovery;	//�ǉ������X�^�~�i�̉񕜗�
	float m_staminaDecrease;	//�y������邳���X�^�~�i�̏���p

public:

	static constexpr int AddHaveInventroy = 1;
	static constexpr int AddHaveWeight = 10;
	static constexpr float AddMaxTheWroldTime = 2;
	static constexpr int AddUseTheWorld = 1;
	static constexpr float AddStaminaRecovery = 2;
	static constexpr float DecreaseStaminaDecrease = -2;

	EnhanceType(int maxHaveInventory,
		int maxHaveWeight,
		float maxTheWorldTime,
		int maxUseTheWorld,
		float staminaRecovery,
		float staminaDecrease) :
		m_onInventoryButton(false),
		m_onHaveWeightButton(false),
		m_onTheWorldTimeButton(false),
		m_onUseTheWorldButton(false),
		m_onStaminaRecoveryButton(false),
		m_onStaminaDecreaseButton(false),
		m_maxHaveInventory(maxHaveInventory),
		m_maxHaveWeight(maxHaveWeight),
		m_maxTheWorldTime(maxTheWorldTime),
		m_maxUseTheWorld(maxUseTheWorld),
		m_staminaRecovery(staminaRecovery),
		m_staminaDecrease(staminaDecrease){};

	enum class EnhanceTypeChoice
	{
		EnhanceInventory,
		EnhanceHaveWeight,
		EnhanceTheWorldTime,
		EnhanceUseTheWorld,
		EnhanceStaminaRecovery,
		EnhanceStaminaDecrease,

		Lenght
	};

	//����
	void Enhance(EnhanceTypeChoice enhanceType)
	{
		switch (enhanceType)
		{
		case EnhanceTypeChoice::EnhanceInventory:
			m_maxHaveInventory += AddHaveInventroy;
			m_onInventoryButton = true;
			break;

		case EnhanceTypeChoice::EnhanceHaveWeight:
			m_maxHaveWeight += AddHaveWeight;
			m_onHaveWeightButton = true;
			break;

		case EnhanceTypeChoice::EnhanceTheWorldTime:
			m_maxTheWorldTime += AddMaxTheWroldTime;
			m_onTheWorldTimeButton = true;
			break;

		case EnhanceTypeChoice::EnhanceUseTheWorld:
			m_maxUseTheWorld += AddUseTheWorld;
			m_onUseTheWorldButton = true;
			break;

		case EnhanceTypeChoice::EnhanceStaminaRecovery:
			m_staminaRecovery += AddStaminaRecovery;
			m_onStaminaRecoveryButton = true;
			break;

		case EnhanceTypeChoice::EnhanceStaminaDecrease:
			m_staminaDecrease += DecreaseStaminaDecrease;
			m_onStaminaDecreaseButton = true;
			break;
		}
	};

	//�{�^�������ꂽ�̂�Ԃ�
	bool OnInventoryButton()
	{
		return m_onInventoryButton;
	}

	bool OnHaveWeightButton()
	{
		return m_onHaveWeightButton;
	}

	bool OnTheWorldTimeButton()
	{
		return m_onTheWorldTimeButton;
	}

	bool OnUseTheWorldButton()
	{
		return m_onUseTheWorldButton;
	}

	bool OnStaminaRecoveryButton()
	{
		return m_onStaminaRecoveryButton;
	}

	bool OnStaminaDecreaseButton()
	{
		return m_onStaminaDecreaseButton;
	}

	//�{�^�����Z�b�g�p
	void InventoryButtonReset()
	{
		m_onInventoryButton = false;
	}

	void HaveWeightButtonReset()
	{
		m_onHaveWeightButton = false;
	}

	void TheWorldButtonTimeReset()
	{
		m_onTheWorldTimeButton = false;
	}

	void UseTheWorldButtonReset()
	{
		m_onUseTheWorldButton = false;
	}

	void StaminaRecoveryButtonReset()
	{
		m_onStaminaRecoveryButton = false;
	}

	void StaminaDecreaseButtonReset()
	{
		m_onStaminaDecreaseButton = false;
	}

	//���������l��Ԃ�
	int GetMaxHaveInventory() const
	{
		return m_maxHaveInventory;
	}

	int GetMaxHaveWeight()
	{
		return m_maxHaveWeight;
	}

	float GetMaxTheWorldTime() const
	{
		return m_maxTheWorldTime;
	}

	int GetMaxUseTheWorldCount() const
	{
		return m_maxUseTheWorld;
	}

	float GetStaminaRecovery() const
	{
		return m_staminaRecovery;
	}

	float GetStaminaDecrease() const
	{
		return m_staminaDecrease;
	}
};