#include "pch.h"
#include "Person.h"
#include "Dices.h"

using namespace DicesNS;

Person::Person()
{
	m_luck = new LuckNS::Luck(false);
}

unsigned Person::hit()
{
	Dices::getInstance()->rollDices();
	takeAction();
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
	takeAction();
	return medKitIndex;
}

Item Person::takeItemToInventory(Item item, int forceTakeIndex/* = -1*/)
{
	takeAction();
	return m_inventory.takeItemToInventory(item, forceTakeIndex);
}

Item Person::dropItemFromInventory(unsigned index)
{
	takeAction();
	return m_inventory.dropItemFromInventory(index);
}

bool Person::swapItemsInInventory(unsigned index1, unsigned index2)
{
	takeAction();
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
	takeAction();
}

int Person::getHealth() const
{
	return m_health;
}

//TODO: think if this method should be a member of Person class
bool Person::hasUmbrellaInHand() const
{
	return m_inventory.hasUmbrellaInHand();
}

const LuckNS::Luck& Person::getLuck() const
{
	return *m_luck;
}

bool Person::stepUp()
{
	m_position.y += 1;
	if (m_position.y > positions::Max_Y)
	{
		m_position.y = positions::Max_Y;
		return false;
	}
	takeAction();
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
	takeAction();
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
	takeAction();
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
	takeAction();
	return true;
}

void Person::addAction(unsigned count/* = 1*/)
{
	m_actions += count;
	if(m_actions > MAX_ACTIONS)
		m_actions = MAX_ACTIONS;
}

void Person::takeAction()
{
	if (m_actions > 0)
		m_actions--;
}






