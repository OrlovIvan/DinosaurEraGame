#include "PlayTable.h"

PlayTable::PlayTable()
{
	m_meteoriteLevel = MeteoriteLevel::getInstance();
	m_weatherDesk = new WeatherDesk(m_meteoriteLevel->getMeteoriteLevel());
	m_weatherCardDeck = WeatherCardDeck::getInstance();
}
