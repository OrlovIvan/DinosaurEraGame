#pragma once

#include "WeatherDesk.h" 
#include "WeatherDeck.h"
#include "MeteoriteLevel.h"
#include "DifficultyConfig.h"

class PlayTable
{
public:
	PlayTable(DifficultyLevel diffLevel);
	~PlayTable() = default;

	void weatherTurn();
private:
	WeatherDesk* m_weatherDesk{};
	WeatherCardDeck* m_weatherCardDeck{};
	MeteoriteLevel* m_meteoriteLevel{};
	DifficultyConfig* m_difficulty{};
};

