#include "Person.h"

inline void Person::damage()
{
	m_health--;
	if (m_health <= 0)
	{
		m_health = 0;
		m_isUnconscious = true;
	}
}

inline void Person::awake()
{
	m_isUnconscious = false;
	m_health = 1;
}

inline void Person::useMedKit()
{
	if (m_hasMedKit)
	{
		m_health = MAX_HEALTH;
		m_hasMedKit = false;
	}
}

inline void Person::eatFood()
{
	if (m_health < MAX_HEALTH && food > 0)
	{
		m_health++;
		food--;
	}
}

inline void Person::takeFood()
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
