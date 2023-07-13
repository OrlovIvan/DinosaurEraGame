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
	return m_inventory[COCCOON_PLACE].getItemName() == ItemName::coccoon;
}

bool Inventory::takeItemToInventory(Item item)
{
	if (item.getItemName() == ItemName::umbrella ||
		item.getItemName() == ItemName::branch || item.getItemName() == ItemName::bat || item.getItemName() == ItemName::gun)
	{
		if (m_inventory[0].getItemName() == ItemName::none)
		{
			m_inventory[0] = item;
			return true;
		}
		else if (m_inventory[1].getItemName() == ItemName::none)
		{
			m_inventory[1] = item;
			return true;
		}
	}

	if (hasCoccoon())
	{
		if (hasFreeSpaceInInventory() != -1)
		{
			m_inventory[hasFreeSpaceInInventory()] = item;
			return true;
		}

	}
	else
	{
		m_inventory[hasFreeSpaceInInventory()] = item;
		return true;
	}
	return false;
}

bool Inventory::hasFreeSpaceInInventory()
{
	for (int i = 0; i < MAX_INVENTORY_COUNT; ++i)
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

int Inventory::hasFood() const
{
	for (int i = 0; i < MAX_INVENTORY_COUNT; ++i)
	{
		if (m_inventory[i].getItemName() == ItemName::food)
			return i;
	}
	return -1;
}
