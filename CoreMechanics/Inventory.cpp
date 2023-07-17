#include "pch.h"
#include "Inventory.h"


using namespace InventoryNS;

Inventory::Inventory()
{
	for (int i = 0;i < MAX_INVENTORY_COUNT;++i)
	{
		m_inventory.push_back(Item(ItemName::none));
	}
}

int Inventory::hasMedKit() const
{
	for (int i = 0; i < MAX_INVENTORY_COUNT; ++i)
	{
		if (m_inventory[i].getItemName() == ItemName::medKit)
			return i;
	}
	return -1;
}

int Inventory::useMedKit()
{
	int medKitIndex = hasMedKit();
	if (medKitIndex != -1)
	{
		m_inventory[medKitIndex] = Item(ItemName::none);
	}
	return medKitIndex;
}

bool Inventory::hasCoccoon() const
{
	return m_inventory[COCCOON_PLACE].getItemName() == ItemName::cocoon;
}

// If Item can be taken to inventory, return ItemName::none
// if not, return item (like a person take the item, cannot hold it and return back to ground)
Item Inventory::takeItemToInventory(Item item, int forceTakeIndex)
{
	if (forceTakeIndex != -1)
	{
		Item swapItem(m_inventory[forceTakeIndex].getItemName());
		m_inventory[forceTakeIndex] = item;
		return swapItem;
	}

	if (item.getItemName() == ItemName::umbrella ||
		item.getItemName() == ItemName::branch || item.getItemName() == ItemName::bat || item.getItemName() == ItemName::gun)
	{
		if (m_inventory[0].getItemName() == ItemName::none)
		{
			m_inventory[0] = item;
			return ItemName::none;
		}
		else if (m_inventory[1].getItemName() == ItemName::none)
		{
			m_inventory[1] = item;
			return ItemName::none;
		}
	}

	if (getFreeSpaceIndexInInventory() != -1)
	{
		m_inventory[getFreeSpaceIndexInInventory()] = item;
		return ItemName::none;
	}
	else
	{
		if (!hasCoccoon() && item.getItemName() == ItemName::cocoon)
		{
			m_inventory[COCCOON_PLACE] = item;
			return ItemName::none;
		}
	}

	return item;
}

Item Inventory::dropItemFromInventory(unsigned index)
{
	Item dropping(m_inventory[index]);

	//we cannot drop a cocoon until we have items inside it
	if (dropping.getItemName() == ItemName::cocoon)
	{
		for (int i = COCCOON_PLACE + 1; i < MAX_INVENTORY_COUNT; ++i)
		{
			if (m_inventory[i].getItemName() != ItemName::none)
				return ItemName::none;
		}
	}
	m_inventory[index] = Item(ItemName::none);
	return dropping;
}

bool Inventory::swapItemsInInventory(unsigned index1, unsigned index2)
{
	if ((index1 >= COCCOON_PLACE || index2 >= COCCOON_PLACE)
		&& m_inventory[COCCOON_PLACE].getItemName() == ItemName::none)
		return false;
	Item temp(m_inventory[index1]);
	m_inventory[index1] = m_inventory[index2];
	m_inventory[index2] = temp;
	return true;
}

int Inventory::getFreeSpaceIndexInInventory()
{
	unsigned maxIndexCount = MAX_INVENTORY_COUNT;
	if (!hasCoccoon())
		maxIndexCount = COCCOON_PLACE;

	for (int i = 0; i < maxIndexCount; ++i)
	{
		if (m_inventory[i].getItemName() == ItemName::none)
			return i;
	}
	return -1;
}

bool Inventory::hasUmbrellaInHand() const
{
	return m_inventory[0].getItemName() == ItemName::umbrella
		|| m_inventory[1].getItemName() == ItemName::umbrella;
}

bool Inventory::eatFood()
{
	int foodIndex = hasFood();
	if (foodIndex != -1)
	{
		m_inventory[foodIndex] = Item(ItemName::none);
		return true;
	}
	return false;
}

const std::vector<Item>& Inventory::getInventory() const
{
	return m_inventory;
}

unsigned Inventory::getWeaponInHandsPower() const
{
	return m_inventory[left].getItemPower() + m_inventory[right].getItemPower();
}

int Inventory::hasFood() const
{
	for (int i = 0; i < MAX_INVENTORY_COUNT; ++i)
	{
		if (m_inventory[i].getItemName() == ItemName::food)
			return i;
	}
	return -1;
}
