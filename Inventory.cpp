#include "Inventory.h"
#include "Screen.h"
#include "ImageLoader.h"
#include "ItemIcon.h"
#include "LoadPlayer.h"
#include "Input.h"
#include "EnhanceType.h"

Inventory::Inventory(EnhanceType* enhanceType) :
	m_maxHaveItem(0),
	m_haveItemCount(0),
	m_canGetItem(false),
	m_itemNum(0),
	m_gettingItem(false),
	m_takeItem(0),
	m_dropItem(false),
	m_nowHaveWeight(0),
	m_dropItemNum(0),
	m_dropItemCompletion(false),
	m_seInventory(0),
	m_enhanceType(enhanceType),
	m_fontTextureId(0)
{
	m_inventoryUi.Register("inventory_ui1.png");
	m_takeItemUi.Register("take_item.png");
	m_slashUi.Register("slash.png");

	//���Ă�A�C�e���̍ő吔��ݒ�
	m_maxHaveItem = m_enhanceType->GetMaxHaveInventory();
}

void Inventory::Load()
{
	//se��ݒ�
	m_seInventory = LoadSoundMem("Resource/sound/move_takeUi.mp3");
	ChangeVolumeSoundMem(128, m_seInventory);

	m_fontTextureId = ImageLoader::GetInstance()->Load("score_font.png");

	m_inventoryUi.Load();
	m_takeItemUi.Load();
	m_slashUi.Load();
}

void Inventory::Release()
{
	DeleteSoundMem(m_seInventory);

	ImageLoader::GetInstance()->Delete("score_font.png");

	m_inventoryUi.Release();
	m_takeItemUi.Release();
	m_slashUi.Release();
}

void Inventory::Update()
{
	m_inventoryUi.Update();
	m_takeItemUi.Update();
	m_slashUi.Update();

	if (m_dropItem)
	{
		m_dropItem = false;
	}
	if (m_gettingItem)
	{
		m_gettingItem = false;
	}

	CheckCanAddItem();

	//�A�C�e�����E�����Ƃ��ł��邩
	if (m_haveItemCount < m_maxHaveItem)
	{
		m_canGetItem = true;
	}
	else 
	{
		m_canGetItem = false;
	}

	if (m_haveItemCount > 0)
	{
		//�A�C�e���I��
		if (Input::GetInstance()->IsKeyDown(KEY_INPUT_Q))
		{
			m_takeItem--;

			PlaySoundMem(m_seInventory, DX_PLAYTYPE_BACK);
		}
		if (Input::GetInstance()->IsKeyDown(KEY_INPUT_E))
		{
			m_takeItem++;

			PlaySoundMem(m_seInventory, DX_PLAYTYPE_BACK);
		}

		//�A�C�e�����̂Ă�
		if (Input::GetInstance()->IsKeyDown(KEY_INPUT_G))
		{
			m_dropItem = true;
			m_dropItemNum = m_takeItem;

			m_nowHaveWeight -= std::next(m_itemList.begin(), m_dropItemNum)->GetItemWeight();
		}
		if (m_dropItemCompletion)
		{
			m_itemList.erase(m_itemList.begin() + m_dropItemNum);

			m_dropItemCompletion = false;
			m_haveItemCount--;
		}
	}

	m_takeItem = m_takeItem % m_maxHaveItem;

	//�����Ă��Ȃ��A�C�e���Ƃ���I���ł��Ȃ��悤�ɂ�����Ȃ�
	if (m_takeItem < 0)
	{
		if (m_haveItemCount == 0)
		{
			m_takeItem = 0;
		}
		else
		{
			m_takeItem = static_cast<int>(m_haveItemCount - 1);
		}
	}
	if (m_takeItem > m_haveItemCount - 1)
	{
		m_takeItem = 0;
	}
	//m_takeItemTransform.position = TakeItemUiPos;

	//Ui�̃|�W�V�����̐ݒ�
	m_takeItemTransform.position = TakeItemUiPos + Vector2(SquareSize * m_takeItem, 0);

	m_slashTransform.position = SlashUiPos;
}

void Inventory::Draw()
{
	//�C���x���g���̘g�̕`��
	for (int i = 0; i <= m_maxHaveItem -1; i++)
	{
		m_inventoryTransform.position = InventoryUiPos + Vector2(SquareSize * i, 0);

		m_inventoryUi.Draw(m_inventoryTransform);
	}

	//���݂̎����Ă���A�C�e���̏d����`��
	Vector2 nowHaveWeightUiPos = Vector2(80, 800);
	nowHaveWeightUiPos.y += FontMargin;
	int nowHaveWeight = m_nowHaveWeight;
	int nowHaveWeightDigit = 1;
	do
	{
		int value = nowHaveWeight % 10;	// 1�̈ʂ̒l�����o��

		DrawRectGraph(
			static_cast<int>(nowHaveWeightUiPos.x - FontSize.x * nowHaveWeightDigit), static_cast<int>(nowHaveWeightUiPos.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		nowHaveWeight /= 10;	// �X�R�A�̌�����
		nowHaveWeightDigit++;		// ���̌���
	} while (nowHaveWeight > 0);

	//���݂̎��Ă�A�C�e���̏d���̍ő�e�ʂ�`��
	Vector2 maxHaveWeightUiPos = Vector2(180, 800);
	maxHaveWeightUiPos.y += FontMargin;
	int maxHaveWeight = m_enhanceType->GetMaxHaveWeight();
	int maxHaveWeightDigit = 1;
	do
	{
		int value = maxHaveWeight % 10;	// 1�̈ʂ̒l�����o��

		DrawRectGraph(
			static_cast<int>(maxHaveWeightUiPos.x - FontSize.x * maxHaveWeightDigit), static_cast<int>(maxHaveWeightUiPos.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		maxHaveWeight /= 10;	// �X�R�A�̌�����
		maxHaveWeightDigit++;		// ���̌���
	} while (maxHaveWeight > 0);

	m_takeItemUi.Draw(m_takeItemTransform);
	m_slashUi.Draw(m_slashTransform);
}

void Inventory::TakeItem(Item* item)
{
	if (m_haveItemCount <= m_maxHaveItem)
	{
		AddChild(new ItemIcon(m_haveItemCount - 1, item, this));

		m_nowHaveWeight += item->GetItemWeight();
	}
}

void Inventory::CheckCanAddItem()
{
	std::vector<Item*> addItemList = m_addItemList;
	m_addItemList.clear();
	for (Item* item : addItemList)
	{
		if (m_haveItemCount >= m_maxHaveItem) break;
		Item i = *item;

		m_itemList.push_back(i);

		AddItemCount();

		TakeItem(item);

		item->DestroyMine();
	}
}
