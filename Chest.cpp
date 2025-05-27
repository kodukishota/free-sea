#include "Chest.h"
#include "MenuInventory.h"
#include "Screen.h"
#include "ImageLoader.h"
#include "ChestItemIcon.h"
#include "LoadPlayer.h"
#include "Input.h"

Chest::Chest() :
	m_haveItemCount(0),
	m_itemNum(0),
	m_destroyTakeItem(0),
	m_takeItem(0),
	m_destroyItemIcon(false),
	m_canStorageItem(true),
	m_isChest(false),
	m_storagingItem(false),
	m_seChest(0)
{
	m_transform.position = Screen::Center + Vector2(0, 170);
	m_chestUi.Register("chest_ui.png");
	m_takeItemUi.Register("take_item.png");
}

void Chest::Load()
{
	//se��ݒ�
	m_seChest = LoadSoundMem("Resource/sound/move_takeUi.mp3");
	ChangeVolumeSoundMem(128, m_seChest);

	m_chestUi.Load();
	m_takeItemUi.Load();
}

void Chest::Release()
{
	DeleteSoundMem(m_seChest);

	m_chestUi.Release();
	m_takeItemUi.Release();
}

void Chest::Update()
{
	m_chestUi.Update();
	m_takeItemUi.Update();

	CheckCanAddItem();

	//�A�C�e�������[�ł��邩
	if (m_haveItemCount >= MaxHaveItem)
	{
		m_canStorageItem = false;
	}
	else
	{
		m_canStorageItem = true;
	}

	//�A�C�e���̃A�C�R�������ׂď����ꂽ������t���O��false��
	if (m_destroyItemIconCount >= m_haveItemCount + 1)
	{
		if (m_destroyItemIcon)
		{
			m_destroyItemIcon = false;
		}

		m_destroyItemIconCount = 0;
	}	

	if (m_haveItemCount >= 0)
	{
		if (m_isChest)
		{
			//�A�C�e���I��
			if (Input::GetInstance()->IsKeyDown(KEY_INPUT_A))
			{
				m_takeItem--;
				PlaySoundMem(m_seChest, DX_PLAYTYPE_BACK);
			}
			else if (Input::GetInstance()->IsKeyDown(KEY_INPUT_D))
			{
				m_takeItem++;
				PlaySoundMem(m_seChest, DX_PLAYTYPE_BACK);
			}
			else if (Input::GetInstance()->IsKeyDown(KEY_INPUT_S))
			{
				m_takeItem += 10;
				PlaySoundMem(m_seChest, DX_PLAYTYPE_BACK);
			}
			else if (Input::GetInstance()->IsKeyDown(KEY_INPUT_W))
			{
				m_takeItem -= 10;
				PlaySoundMem(m_seChest, DX_PLAYTYPE_BACK);
			}
		}
	}

	m_takeItem = m_takeItem % MaxHaveItem;

	//�����Ă��Ȃ��A�C�e���Ƃ���I���ł��Ȃ��悤�ɂ�����Ȃ�
	if (m_takeItem < 0)
	{
		if (m_haveItemCount == 0)
		{
			m_takeItem = 0;
		}
		else
		{
			m_takeItem = m_haveItemCount - 1;
		}
	}
	if (m_takeItem > m_haveItemCount - 1)
	{
		m_takeItem = 0;
	}

	//����
	int verticalCount = m_takeItem / 10;
	if (m_takeItem >= 10)
	{
		int takeItem = m_takeItem % 10;

		m_takeItemTransform.position = TakeItemUiPos + Vector2(90 * takeItem, 90 * verticalCount);
	}
	else
	{
		m_takeItemTransform.position = TakeItemUiPos + Vector2(90 * m_takeItem, 0);
	}
}

void Chest::Draw()
{
	m_chestUi.Draw(m_transform);
	if (m_isChest)
	{
		m_takeItemUi.Draw(m_takeItemTransform);
	}
}

void Chest::CreateIcon(Item* item)
{
	if (m_haveItemCount <= MaxHaveItem)
	{
		AddChild(new ChestItemIcon(m_haveItemCount - 1, item, this));
	}
}

void Chest::CheckCanAddItem()
{
	std::vector<Item*> addItemList = m_addItemList;
	m_addItemList.clear();
	for (Item* item : addItemList)
	{
		if (m_haveItemCount >= MaxHaveItem) break;

		if (m_haveItemCount >= MaxHaveItem) break;
		Item i = *item;

		m_itemList.push_back(i);

		AddItemCount();

		CreateIcon(item);

		item->DestroyMine();
	}
}