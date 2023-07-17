#include "pch.h"
#include "Person.h"
#include "Dices.h"


Person::Person()
{
	
}

unsigned Person::hit()
{
	Dices::getInstance()->tossDices();
	return m_inventory.getWeaponInHandsPower() + Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
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

int Person::useMedKit()
{
	int medKitIndex = m_inventory.useMedKit();
	if (medKitIndex != -1)
	{
		m_health = MAX_HEALTH;
	}
	return medKitIndex;
}

Item Person::takeItemToInventory(Item item, int forceTakeIndex/* = -1*/)
{
	return m_inventory.takeItemToInventory(item, forceTakeIndex);
}

Item Person::dropItemFromInventory(unsigned index)
{
	return m_inventory.dropItemFromInventory(index);
}

bool Person::swapItemsInInventory(unsigned index1, unsigned index2)
{
	return m_inventory.swapItemsInInventory(index1, index2);
}

const std::vector<Item>& Person::getInventory() const
{
	return m_inventory.getInventory();
}

void Person::eatFood()
{
	bool isEaten = m_inventory.eatFood();
	if (isEaten && m_health < MAX_HEALTH)
	{
		m_health++;
	}
}

int Person::getHealth() const
{
	return m_health;
}

bool Person::hasUmbrellaInHand() const
{
	return m_inventory.hasUmbrellaInHand();
}

bool Person::stepUp()
{
	m_position.y += 1;
	if (m_position.y > positions::Max_Y)
	{
		m_position.y = positions::Max_Y;
		return false;
	}
	return true;
}

bool Person::stepDown()
{
	m_position.y -= 1;
	if (m_position.y < positions::Min_Y)
	{
		m_position.y = positions::Min_Y;
		return false;
	}
	return true;
}

bool Person::stepRight()
{
	m_position.x += 1;
	if (m_position.x > positions::Max_X)
	{
		m_position.x = positions::Max_X;
		return false;
	}
	return true;
}

bool Person::stepLeft()
{
	m_position.x -= 1;
	if (m_position.x < positions::Min_X)
	{
		m_position.x = positions::Min_X;
		return false;
	}
	return true;
}






