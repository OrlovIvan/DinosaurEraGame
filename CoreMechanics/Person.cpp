#include "pch.h"
#include "Person.h"

void Person::damage()
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

inline void Person::takeMedKit()
{
	m_hasMedKit = true;
}

void Person::takeUmbrella()
{
	m_hasUmbrella = true;
}

int Person::getHealth() const
{
	return m_health;
}
