#include "pch.h"
#include <iostream>
#include <vector>
#include "WeatherDeck.h"
#include "DifficultyConfig.h"

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

vector<WeatherCard> WeatherCardDeck::turn(unsigned meteoriteLevel, const vector<int>& weatherDeskCardCount)
{
	vector<WeatherCard> newCards;
	unsigned& cardCount = meteoriteLevel; //just a name alias
	for (int i = 0; i < cardCount; ++i)
	{
		if (m_deck.empty())
		{
			fillDeck(newCards, weatherDeskCardCount);
			shuffle();
		}
		
		newCards.push_back(m_deck.top());
		m_deck.pop();
	}
	return newCards;
}

void WeatherCardDeck::print()
{
	if (m_deck.empty())
	{
		cout << "WeatherDeck is empty!" << endl;
		return;
	}
	
	vector<WeatherCard> cardsInDeck = testGetAllCardsInDeck();
	
	for(auto card : cardsInDeck)
		printCard(card);
		
	cout << endl;
}

void WeatherCardDeck::fillDeck(const vector<WeatherCard> newCards, const vector<int> weatherDeskCardCount)
{
	DifficultyConfig* difficulty = DifficultyConfig::getInstance();
	vector<int> cardsInGame(weatherDeskCardCount);
	if (!cardsInGame.size()) // if the weatherDeskCardCount was empty (initial creation of the cardDeck), fill the vector by 0s
	{
		for (int i = 0; i <= WeatherCard::end; ++i)
			cardsInGame.push_back(0);
	}

	// check if newCards has something and add them to the cards "in game now" not to count them during deck refilling
	for (const WeatherCard& card : newCards)
	{
		cardsInGame[card]++;
	}

	for (int i = 0; i < difficulty->getWeatherCardCountClean() - cardsInGame[WeatherCard::Clean]; ++i)
		m_deck.push(WeatherCard::Clean);

	for (int i = 0; i < difficulty->getWeatherCardCountClowdy() - cardsInGame[WeatherCard::Clowdy]; ++i)
		m_deck.push(WeatherCard::Clowdy);

	for (int i = 0; i < difficulty->getWeatherCardCountOzon() - cardsInGame[WeatherCard::OzonHole]; ++i)
		m_deck.push(WeatherCard::OzonHole);

	for (int i = 0; i < difficulty->getWeatherCardCountLightning() - cardsInGame[WeatherCard::Lightning]; ++i)
		m_deck.push(WeatherCard::Lightning);

	for (int i = 0; i < difficulty->getWeatherCardCountThunder() - cardsInGame[WeatherCard::Thunder]; ++i)
		m_deck.push(WeatherCard::Thunder);

	for (int i = 0; i < difficulty->getWeatherCardCountMeteorite() - cardsInGame[WeatherCard::Meteorite]; ++i)
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

vector<WeatherCard> WeatherCardDeck::testGetAllCardsInDeck()
{
	vector<WeatherCard> deck;

	stack<WeatherCard> temp;
	while (!m_deck.empty())
	{
		temp.push(m_deck.top());
		deck.push_back(m_deck.top());
		m_deck.pop();
	}

	while (!temp.empty())
	{
		m_deck.push(temp.top());
		temp.pop();
	}

	return deck;
}
