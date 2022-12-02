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
    vector<int> cardsCount;
    for (int i = 0; i <= WeatherCard::end; ++i)
        cardsCount.push_back(0);
    for (auto card : deck)
    {
        cardsCount[card]++;
    }
    EXPECT_EQ(cardsCount[WeatherCard::Clean],CLEAN_COUNT);
    EXPECT_EQ(cardsCount[WeatherCard::Clowdy], CLOWDY_COUNT);
    EXPECT_EQ(cardsCount[WeatherCard::Lightning], LIGHTNING_COUNT);
    EXPECT_EQ(cardsCount[WeatherCard::Meteorite], METEORITE_COUNT);
    EXPECT_EQ(cardsCount[WeatherCard::OzonHole], OZON_COUNT);
    EXPECT_EQ(cardsCount[WeatherCard::Thunder], THUNDER_COUNT);

    vector<WeatherCard> cardsInGame = weatherDeck->turn(2, vector<int>());

    vector<WeatherCard> deckAfterTurn = weatherDeck->testGetAllCardsInDeck();
    vector<WeatherCard> resultDeck;

    for(auto card : cardsInGame)
        resultDeck.push_back(card);
    for (auto card : deckAfterTurn)
        resultDeck.push_back(card);

    EXPECT_EQ(resultDeck.size(), deck.size());
    bool isEqual = true;

    for (int i = 0; i < resultDeck.size(); ++i)
    {
        if (resultDeck[i] != deck[i])
        {
            isEqual = false;
            break;
        }
    }
    EXPECT_TRUE(isEqual);

    // make the deck get empty and shuffle again. Then compare the initial deck and newly shuffled
    resultDeck.clear();
    cardsInGame = weatherDeck->turn(48, vector<int>());
    cardsInGame = weatherDeck->turn(1, vector<int>());
    deckAfterTurn = weatherDeck->testGetAllCardsInDeck();
    for (auto card : cardsInGame)
        resultDeck.push_back(card);
    for (auto card : deckAfterTurn)
        resultDeck.push_back(card);
    EXPECT_EQ(resultDeck.size(), deck.size());

    int initialCRC = 0;
    int newDeckCRC = 0;
    for (int i = 0; i < resultDeck.size(); ++i)
    {
        initialCRC += (deck[i]+1) * (i+1);
        newDeckCRC += (resultDeck[i]+1) * (i+1);
    }
    EXPECT_TRUE(initialCRC != newDeckCRC);

    weatherDeck->print();
}

TEST(TestWeatherDesk, TestDeskHandling)
{
    WeatherDesk* desk = WeatherDesk::getInstance(5);
    vector<WeatherCard> cardsToPush{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Lightning, WeatherCard::Meteorite, WeatherCard::OzonHole };
    desk->testFillTheDesk(cardsToPush, 5);
    vector<WeatherCard> cardsOnDesk = desk->testGetAllCardsInDesk();
    
    EXPECT_EQ(cardsOnDesk.size(), cardsToPush.size());

    bool isEqual = true;
    for (int i = 0; i < cardsOnDesk.size(); ++i)
    {
        if (cardsOnDesk[i] != cardsToPush[cardsOnDesk.size()-i-1])
        {
            isEqual = false;
            break;
        }
    }
    EXPECT_TRUE(isEqual);
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