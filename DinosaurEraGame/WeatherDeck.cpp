#include <iostream>
#include <vector>
#include "WeatherDeck.h"

WeatherCardDeck* WeatherCardDeck::classPtr = nullptr;

WeatherCardDeck::WeatherCardDeck()
{
	fillDeck();
	shuffle();
}

void WeatherCardDeck::shuffle()
{
	vector<WeatherCard> temp;
	while (!m_deck.empty())
	{
		temp.push_back(m_deck.top());
		m_deck.pop();
	}

	for (int i = 0; i < temp.size(); ++i)
	{
		int ind = std::rand()% temp.size();
		swap(temp[i], temp[ind]);
	}

	for (int i = 0; i < temp.size(); ++i)
	{
		m_deck.push(temp.at(i));
	}
}

void WeatherCardDeck::turn(int cardCount)
{
	for (int i = 0; i < cardCount; ++i)
	{
		if (!m_deck.empty())
		{
			m_weatherDesk.putCardOnDesk(m_deck.top());
			m_deck.pop();
		}
		else
		{
			fillDeck();
			shuffle();
		}

		m_weatherDesk.popCardFromDesk();
	}
}

void WeatherCardDeck::print()
{
	if (m_deck.empty())
	{
		cout << "WeatherDeck is empty!" << endl;
		return;
	}
	
	stack<WeatherCard> temp;
	while (!m_deck.empty())
	{
		temp.push(m_deck.top());
		printCard(m_deck.top());
		m_deck.pop();
	}

	while (!temp.empty())
	{
		m_deck.push(temp.top());
		temp.pop();
	}

	cout << endl;

	m_weatherDesk.printDesk();
	m_weatherDesk.printCounts();
}



const WeatherDesk& WeatherCardDeck::getWeatherDesk() const
{
	return m_weatherDesk;
}

void WeatherCardDeck::fillDeck()
{
	while(!m_deck.empty())
		m_deck.pop();

	for (int i = 0; i < CLEAN_COUNT- m_weatherDesk.getCardCount(WeatherCard::Clean); ++i)
		m_deck.push(WeatherCard::Clean);

	for (int i = 0; i < CLOWDY_COUNT; ++i)
		m_deck.push(WeatherCard::Clowdy);

	for (int i = 0; i < OZON_COUNT; ++i)
		m_deck.push(WeatherCard::OzonHole);

	for (int i = 0; i < LIGHTNING_COUNT; ++i)
		m_deck.push(WeatherCard::Lightning);

	for (int i = 0; i < THUNDER_COUNT; ++i)
		m_deck.push(WeatherCard::Thunder);

	for (int i = 0; i < METEORITE_COUNT; ++i)
		m_deck.push(WeatherCard::Meteorite);
}

void printCard(WeatherCard& card)
{
	switch (card)
	{
	case WeatherCard::Clean:
		cout << " Clean ";
			break;
	case WeatherCard::Clowdy:
		cout << " Clowdy ";
		break;
	case WeatherCard::OzonHole:
		cout << " OzonHole ";
		break;
	case WeatherCard::Lightning:
		cout << " Lightning ";
		break;
	case WeatherCard::Thunder:
		cout << " Thunder ";
		break;
	case WeatherCard::Meteorite:
		cout << " Meteorite ";
		break;
	}
}


