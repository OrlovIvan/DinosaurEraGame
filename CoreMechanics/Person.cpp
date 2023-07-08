#include "pch.h"
#include "Person.h"

Person::Person()
{
	for (int i = 0;i < MAX_INVENTORY_COUNT;++i)
	{
		m_inventory.push_back(Item(ItemName::none));
	}
}

void Person::hit()
{
	
}

void Person::getHit()
{
	m_health--;
	if (m_health <= 0)
	{
		m_health = 0;
		m_isUnconscious = true;
	}
}

void Person::awake()
{
	m_isUnconscious = false;
	m_health = 1;
}

void Person::useMedKit()
{
	int medKitIndex = hasMedKit();
	if (medKitIndex != -1)
	{
		m_health = MAX_HEALTH;
		m_inventory[medKitIndex] = Item(ItemName::none);
	}
}

bool Person::takeItemToInventory(Item item)
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

void Person::eatFood()
{
	if (m_health < MAX_HEALTH && food > 0)
	{
		m_health++;
		food--;
	}
}

void Person::takeFood()
{
	food++;
}

void Person::takeUmbrella()
{
	
}

int Person::getHealth() const
{
	return m_health;
}

bool Person::hasUmbrellaInHand() const
{
	return m_inventory[0].getItemName() == ItemName::umbrella
			|| m_inventory[1].getItemName() == ItemName::umbrella;
}

bool Person::hasFreeSpaceInInventory()
{
	for (int i = 0; i < MAX_INVENTORY_COUNT; ++i)
	{
		if (m_inventory[i].getItemName() == ItemName::none)
			return i;
	}
	return -1;
}

bool Person::stepUp()
{
	return false;
}

bool Person::stepDown()
{
	return false;
}

bool Person::stepRight()
{
	return false;
}

bool Person::stepLeft()
{
	return false;
}

int Person::hasMedKit() const
{
	for (int i = 0; i < MAX_INVENTORY_COUNT; ++i)
	{
		if (m_inventory[i].getItemName() == ItemName::medKit)
			return i;
	}
	return -1;
}

bool Person::hasCoccoon() const
{
	return m_inventory[COCCOON_PLACE].getItemName() == ItemName::coccoon;
}
