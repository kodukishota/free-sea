#include "Inventory.h"
#include "Screen.h"
#include "ImageLoader.h"
#include "ItemIcon.h"
#include "LoadPlayer.h"
#include "Input.h"

Inventory::Inventory() :
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
	m_fontTextureId(0)
{
	m_inventoryUi.Register("inventory_ui1.png");
	m_takeItemUi.Register("take_item.png");
	m_slashUi.Register("slash.png");
}

void Inventory::Load()
{
	//seを設定
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

	//アイテムを拾うことができるか
	if (m_haveItemCount < m_maxHaveItem)
	{
		m_canGetItem = true;
	}
	else 
	{
		m_canGetItem = false;
	}

	//Uiのポジションの設定
	m_takeItemTransform.position = TakeItemUiPos + Vector2(SquareSize * m_takeItem, 0);

	m_slashTransform.position = SlashUiPos;
}

void Inventory::Draw()
{
	//インベントリの枠の描画
	for (int i = 0; i <= m_maxHaveItem -1; i++)
	{
		m_inventoryTransform.position = InventoryUiPos + Vector2(SquareSize * i, 0);

		m_inventoryUi.Draw(m_inventoryTransform);
	}

	m_takeItemUi.Draw(m_takeItemTransform);
	m_slashUi.Draw(m_slashTransform);
}

void Inventory::TakeItem(Item* item)
{
	if (m_haveItemCount <= m_maxHaveItem)
	{
		AddChild(new ItemIcon(m_haveItemCount - 1, item, this));

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
