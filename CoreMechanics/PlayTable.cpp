#include "pch.h"
#include "PlayTable.h"
#include "Astronomer.h"
#include "Doctor.h"
#include "Thief.h"
#include "Inventor.h"
#include "Policeman.h"
#include "Historian.h"
#include "WeatherDeck.h"

PlayTable::PlayTable(DifficultyLevel diffLevel)
{
    m_difficulty = DifficultyConfig::getInstance(diffLevel);
	m_meteoriteLevel = MeteoriteLevel::getInstance();
	m_weatherDesk = WeatherDesk::getInstance(m_meteoriteLevel->getMeteoriteLevel());
	m_weatherCardDeck = WeatherCardDeck::getInstance();
}

void PlayTable::weatherTurn()
{
	//players turn
	//card deck turn. Get new weather cards
	//push new cards to the weather desk
	//get weather conditions (isgameOver? What to do with players if not)
    Astronomer astronomer;
    Doctor doctor;
    Thief thief;
    Inventor inventor;
    Policeman policeman;
    Historian historian;
    vector<Person*> persons{ &astronomer, &doctor, &thief, &policeman, &inventor, &historian };

    for (auto person : persons)
    {
        person->takeFood();
        person->takeFood();
        person->takeFood();
    }

    /*while (weatherDeck->getMeteoriteLevel() != 6)
    {
        bool medKit = true;
        bool umbrella = true;

        if (weatherDeck->getMeteoriteLevel() == 4 && medKit)
        {
            for (auto person : persons)
            {
                person->takeMedKit();
            }
            medKit = false;
        }

        if (weatherDeck->getMeteoriteLevel() == 3 && umbrella)
        {
            for (auto person : persons)
            {
                person->takeUmbrella();
            }
            umbrella = false;
        }

        weatherDeck->turn();
        if (weatherDeck->getWeatherDesk().getDamageFromWeather(WeatherCard::OzonHole) != WeatherDamage::Null)
        {

        }
    }*/
}
