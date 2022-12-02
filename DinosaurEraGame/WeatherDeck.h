#pragma once
#include <stack>
#include <queue>
#include <vector>

using namespace std;

#define CLEAN_COUNT (20)
#define CLOWDY_COUNT (9)
#define OZON_COUNT (4)
#define LIGHTNING_COUNT (4)
#define THUNDER_COUNT (10)
#define METEORITE_COUNT (3)

enum WeatherCard
{
	Clean = 0,
	Clowdy,
	OzonHole,
	Lightning,
	Thunder,
	Meteorite,
	end = Meteorite
};

void printCard(WeatherCard&);

class WeatherDesk;

class WeatherCardDeck
{
public:
	~WeatherCardDeck() {};

	void shuffle();
	void turn(int cardCount);

	void print();

	static WeatherCardDeck* getInstance()
	{
		if (!classPtr)
		{
			classPtr = new WeatherCardDeck();
		}
		return classPtr;
	}

	const WeatherDesk& getWeatherDesk() const;
	
private:
	WeatherCardDeck();

	static WeatherCardDeck* classPtr;

	void fillDeck();
	std::stack<WeatherCard> m_deck;
};

