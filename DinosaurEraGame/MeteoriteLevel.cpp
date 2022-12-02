#include <iostream>
#include "MeteoriteLevel.h"

#define SUB_LEVEL_MAX (3)

using namespace std;

MeteoriteLevel* MeteoriteLevel::instance = nullptr;

unsigned MeteoriteLevel::getMeteoriteLevel() const
{
    return m_meteoriteLevel;
}

bool MeteoriteLevel::incrementMeteoriteLevel()
{
	//подуровень метеорита. Как только достигнет 3, близость метеорита увеличивается
	if (m_sublevel != SUB_LEVEL_MAX)
	{
		m_sublevel++;
		return false;
	}
	m_sublevel = 0;

	m_meteoriteLevel++;
	return true;
}

void MeteoriteLevel::decrementMeteoriteLevel()
{
	if (m_sublevel > 0)
		m_sublevel--;
	else
	{
		m_sublevel = SUB_LEVEL_MAX;
		m_sublevel--;
		m_meteoriteLevel--;
	}
}

bool MeteoriteLevel::isGameOver() const
{
	bool isHit = m_meteoriteLevel < METEORITE_STRIKE_LEVEL ? false : true;
	if(isHit)
		cout << " Game is over. Meteorite hits the Earth!" << endl;
    return isHit;
}

void MeteoriteLevel::testSetClass(unsigned level, unsigned subLevel)
{
	m_meteoriteLevel = level;
	m_sublevel = subLevel;
}

void MeteoriteLevel::print() const
{
	cout << "Meteorite level = " << m_meteoriteLevel << " subLevel = " << m_sublevel << endl;
}
