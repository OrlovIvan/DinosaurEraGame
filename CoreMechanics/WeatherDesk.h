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
	static WeatherDesk* getInstance(unsigned meteoriteLevel = 2)
	{
		if (!instance)
		{
			instance = new WeatherDesk(meteoriteLevel);
		}
		return instance;
	}

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

	WeatherDesk() = delete;
	WeatherDesk(unsigned meteoriteLevel);

	static WeatherDesk* instance;

	void setDeskLevel(int meteoriteLevel);

	std::queue<WeatherCard> m_weatherDesk;
	std::vector<int> m_cardCountOnDesk;

	unsigned int m_weatherDeskLevel;
};

