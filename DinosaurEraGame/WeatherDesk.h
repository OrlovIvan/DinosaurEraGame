#pragma once
#include "WeatherDeck.h"

class WeatherCardDeck;

enum class WeatherDamage
{
	Null = 0,
	One,
	All
};

class WeatherDesk
{
public:
	WeatherDesk() = delete;
	WeatherDesk(unsigned meteoriteLevel) : m_weatherDeskLevel(meteoriteLevel + 1) {}

	void putCardOnDesk(WeatherCard&);
	void popCardFromDesk();

	int getCardCount(WeatherCard cardType) const
	{
		return m_cardCountOnDesk[cardType];
	}

	WeatherDamage getDamageFromWeather(WeatherCard damageCard) const;

	void printDesk();
	void printCounts();

	void testFillTheDesk(std::vector<WeatherCard>& vec, int level);
private:
	friend class PlayTable;

	void setDeskLevel(int meteoriteLevel);

	std::queue<WeatherCard> m_weatherDesk;
	std::vector<int> m_cardCountOnDesk;

	unsigned int m_weatherDeskLevel;
};

