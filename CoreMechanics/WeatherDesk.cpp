#include "pch.h"
#include <iostream>
#include <vector>
#include "WeatherDesk.h"

WeatherDesk* WeatherDesk::instance = nullptr;

WeatherDesk::WeatherDesk(unsigned meteoriteLevel) : m_weatherDeskLevel(meteoriteLevel + 1)
{
	m_cardCountOnDesk.clear();
	for (int i = 0; i <= WeatherCard::end; ++i)
		m_cardCountOnDesk.push_back(0);
}

void WeatherDesk::putCardOnDesk(WeatherCard& card)
{
	m_weatherDesk.push(card);
	m_cardCountOnDesk[card]++;
}

void WeatherDesk::popCardFromDesk()
{
	if (m_weatherDesk.size() > m_weatherDeskLevel)
	{
		m_cardCountOnDesk[m_weatherDesk.front()]--;
		m_weatherDesk.pop();
	}
}

void WeatherDesk::setDeskLevel(int meteoriteLevel)
{
	switch (meteoriteLevel)
	{
	case 2: m_weatherDeskLevel = 3; break;
	case 3: m_weatherDeskLevel = 4; break;
	case 4:
	case 5: m_weatherDeskLevel = 5; break;
	default:
		cout << "Error! Weather Desk level is more than 5!" << endl;
		throw("WetherDeskError");
		break;
	}
}

WeatherDamage WeatherDesk::getDamageFromWeather(WeatherCard damageCard) const
{
	if (damageCard < WeatherCard::OzonHole || damageCard > WeatherCard::Lightning)
		return WeatherDamage::Null;

	if (damageCard == WeatherCard::OzonHole)
	{
		if (getCardCount(WeatherCard::OzonHole) == 0
			|| getCardCount(WeatherCard::Thunder) != 0)
			return WeatherDamage::Null;
		else if (getCardCount(WeatherCard::Clowdy) != 0)
			return WeatherDamage::One;
		return WeatherDamage::All;
	}

	if (damageCard == WeatherCard::Lightning)
	{
		if (getCardCount(WeatherCard::Lightning) == 0)
			return WeatherDamage::Null;
		else if (getCardCount(WeatherCard::Thunder) != 0)
			return WeatherDamage::All;
		return WeatherDamage::One;
	}
	return WeatherDamage::Null;
}

void WeatherDesk::printDesk()
{
	cout << "---------------" << endl;
	cout << "Weather desk:" << endl;
	queue<WeatherCard> temp;
	while (!m_weatherDesk.empty())
	{
		temp.push(m_weatherDesk.front());
		printCard(m_weatherDesk.front());
		m_weatherDesk.pop();
	}
	while (!temp.empty())
	{
		m_weatherDesk.push(temp.front());
		temp.pop();
	}
	cout << endl;
	cout << "---------------" << endl;
}

void WeatherDesk::printCounts()
{
	cout << "---------------" << endl;
	cout << "Weather printCounts:" << endl;
	cout << " Clean: " << m_cardCountOnDesk[WeatherCard::Clean];
	cout << " Clowdy: " << m_cardCountOnDesk[WeatherCard::Clowdy];
	cout << " Lightning: " << m_cardCountOnDesk[WeatherCard::Lightning];
	cout << " OzonHole: " << m_cardCountOnDesk[WeatherCard::OzonHole];
	cout << " Thunder: " << m_cardCountOnDesk[WeatherCard::Thunder];
	cout << " Meteorite: " << m_cardCountOnDesk[WeatherCard::Meteorite] << endl;
	cout << "---------------" << endl;
}

void WeatherDesk::testFillTheDesk(vector<WeatherCard>& vec, int level)
{
	setDeskLevel(level);
	for (auto card : vec)
	{
		putCardOnDesk(card);
	}
}
