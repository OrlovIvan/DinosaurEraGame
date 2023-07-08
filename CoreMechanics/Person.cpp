#include "pch.h"
#include "Person.h"

inline Person::Person()
{
	for (int i = 0;i < MAX_INVENTORY_COUNT;++i)
	{
		m_inventory.push_back(Item(ItemName::none));
	}
}

void Person::hit()
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
	if (m_hasMedKit)
	{
		m_health = MAX_HEALTH;
		m_hasMedKit = false;
	}
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
	m_hasUmbrella = true;
}

int Person::getHealth() const
{
	return m_health;
}

bool Person::hasFreeSpaceInInventory()
{
	for (auto item : m_inventory)
	{
		if (item.getItemName() == ItemName::none)
			return true;
	}
	return false;
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
