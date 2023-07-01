#pragma once
#include "WeatherCardDeck.h"

class WeatherCardDeck;

enum class WeatherDamage
{
	Null = 0,
	One,
	All
#pragma TODO("Ivan","For future getting multiple damage from multiple ozon holes and lightnings")
	//,Multiple
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

	void putCardsOnDesk(const vector<WeatherCard>&);

	int getCardCount(WeatherCard cardType) const
	{
		return m_cardCountOnDesk[cardType];
	}

	WeatherDamage getDamageFromWeather(WeatherCard damageCard) const;

	void printDesk();
	void printCounts();

	void testFillTheDesk(std::vector<WeatherCard>& vec, int level);
	vector<WeatherCard> testGetAllCardsInDesk();
private:
	friend class PlayTable;

	WeatherDesk() = delete;
	WeatherDesk(unsigned meteoriteLevel);

	static WeatherDesk* instance;

	void pushCardToDesk(const WeatherCard& card);
	void popInvalidCardsFromDesk();

	void setDeskLevel(int meteoriteLevel);

	std::queue<WeatherCard> m_weatherDesk;
	std::vector<int> m_cardCountOnDesk;

	unsigned int m_weatherDeskLevel;
};

