#include "pch.h"
#include "MeteoriteLevel.h"
#include "WeatherDeck.h"
#include "WeatherDesk.h"
#include "Test.h"
#include <iostream>

using namespace std;

TEST(TestMeteoriteLevel, TestLevelHandling)
{
    cout << "Meteorite test." << endl;
    MeteoriteLevel* metLevel = MeteoriteLevel::getInstance();

    metLevel->incrementMeteoriteLevel();
    metLevel->incrementMeteoriteLevel();
    metLevel->incrementMeteoriteLevel();
    EXPECT_EQ(metLevel->getMeteoriteLevel(), 3);

    metLevel->decrementMeteoriteLevel();
    EXPECT_EQ(metLevel->getMeteoriteLevel(), 2);

    metLevel->incrementMeteoriteLevel(); // make the meteorite level equal to 3
    for (int i = 0; metLevel->getMeteoriteLevel() != 6; ++i)
    {
	    metLevel->incrementMeteoriteLevel();
    }
    EXPECT_TRUE(metLevel->isGameOver());
}

TEST(TestWeatherCardDeck, TestDeckHandling)
{
	WeatherCardDeck* weatherDeck = WeatherCardDeck::getInstance();

    vector<WeatherCard> deck = weatherDeck->testGetAllCardsInDeck();
    vector<WeatherCard> cardsInGame = weatherDeck->turn(2, vector<int>());

    vector<WeatherCard> deckAfterTurn = weatherDeck->testGetAllCardsInDeck();
    vector<WeatherCard> resultDeck;
    for (auto card : cardsInGame)
        resultDeck.push_back(card);
    for (auto card : deckAfterTurn)
        resultDeck.push_back(card);

    EXPECT_EQ(resultDeck.size(), deck.size());
    bool isEqual = false;

    for (int i = 0; i < resultDeck.size(); ++i)
    {
        if (resultDeck[i] != deck[i])
        {
            isEqual = false;
            break;
        }
    }
    EXPECT_TRUE(isEqual);

    weatherDeck->print();
}

TEST(TestWeatherDesk, TestDeskHandling)
{
    /*cout << "***** Test weather damage *****" << endl;

    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Thunder };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::Null) ? "true" : "false";
        cout << "Ozon, no ozon holes: " << answer << endl;
    }
    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::OzonHole };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::All) ? "true" : "false";
        cout << "Ozon, clear sky: " << answer << endl;
    }
    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::OzonHole };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::One) ? "true" : "false";
        cout << "Ozon, clowdy sky: " << answer << endl;
    }

    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Clean, WeatherCard::OzonHole, WeatherCard::Thunder };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::Null) ? "true" : "false";
        cout << "Ozon, thunder sky: " << answer << endl;
    }

    //------------------
    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::Null) ? "true" : "false";
        cout << "Lightning, no lightning, clean: " << answer << endl;
    }
    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Thunder, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::Null) ? "true" : "false";
        cout << "Lightning, no lightning, thunder: " << answer << endl;
    }
    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Lightning, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::One) ? "true" : "false";
        cout << "Lightning, clear sky: " << answer << endl;
    }

    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Thunder, WeatherCard::Lightning, WeatherCard::Clean, WeatherCard::Clean };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::All) ? "true" : "false";
        cout << "Lightning, lightning, thunder: " << answer << endl;
    }

    {
        WeatherDesk desk;
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Lightning, WeatherCard::Thunder, WeatherCard::Lightning, WeatherCard::Thunder, WeatherCard::Clean };
        desk.testFillTheDesk(cardsOnDesk, 5);
        string answer = (desk.getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::All) ? "true" : "false";
        cout << "Lightning, lightning*2, thunder*2: " << answer << endl;
    }*/
}