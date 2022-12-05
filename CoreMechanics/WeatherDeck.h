#pragma once
#include <stack>
#include <queue>
#include <vector>

using namespace std;

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

	vector<WeatherCard> turn(unsigned meteoriteLevel, const vector<int>& weatherDeskCardCount);

	void print();

	static WeatherCardDeck* getInstance()
	{
		if (!classPtr)
		{
			classPtr = new WeatherCardDeck();
		}
		return classPtr;
	}

	vector<WeatherCard> testGetAllCardsInDeck();
	void testFill() { 
		while (!m_deck.empty())
			m_deck.pop();
		fillDeck(); }
private:
	WeatherCardDeck();
	static WeatherCardDeck* classPtr;

	void fillDeck(const vector<WeatherCard> newCards = vector<WeatherCard>(), const vector<int> weatherDeskCardCount = vector<int>());
	void shuffle();
	std::stack<WeatherCard> m_deck;
};

