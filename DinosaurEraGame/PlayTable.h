#pragma once

#include "WeatherDesk.h" 
#include "WeatherDeck.h"
#include "MeteoriteLevel.h"

class PlayTable
{
public:
	PlayTable();
	~PlayTable() = default;
private:
	WeatherDesk* m_weatherDesk{};
	WeatherDeck* m_weatherCardDeck{};
	MeteoriteLevel* m_meteoriteLevel{};
};

