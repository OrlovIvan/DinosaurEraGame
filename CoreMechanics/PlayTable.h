#pragma once

#include "WeatherDesk.h" 
#include "WeatherDeck.h"
#include "MeteoriteLevel.h"

class PlayTable
{
public:
	PlayTable();
	~PlayTable() = default;

	void weatherTurn();
private:
	WeatherDesk* m_weatherDesk{};
	WeatherCardDeck* m_weatherCardDeck{};
	MeteoriteLevel* m_meteoriteLevel{};
};

