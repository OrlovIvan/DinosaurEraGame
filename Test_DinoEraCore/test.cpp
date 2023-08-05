#include <iostream>

#include "pch.h"
#include "MeteoriteLevel.h"
#include "WeatherCardDeck.h"
#include "WeatherDesk.h"
#include "Test.h"
#include "DifficultyConfig.h"
#include "ProbabilitiesTestMethods.h"
#include "Items.h"
#include "Person.h"
#include "Policeman.h"
#include "Dices.h"

using namespace std;
using namespace DicesNS;

TEST(TestItem)
{
    Item item(ItemName::none);
    EXPECT_TRUE(item.getItemName() == ItemName::none);
}

TEST(TestRandomGenerator, TestDices)
{
    Dices* dices = Dices::getInstance();
    
    auto dice1 = dices->getFirstDiceValue();
    auto dice2 = dices->getSecondDiceValue();

    EXPECT_TRUE(dices->getFirstDiceValue() > 0 && dices->getFirstDiceValue() <= 6);
    EXPECT_TRUE(dices->getSecondDiceValue() > 0 && dices->getSecondDiceValue() <= 6);
    dices->rollDices();
    EXPECT_TRUE(dices->getFirstDiceValue() > 0 && dices->getFirstDiceValue() <= 6);
    EXPECT_TRUE(dices->getSecondDiceValue() > 0 && dices->getSecondDiceValue() <= 6);
}

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

TEST(TestDifficultyConfig, TestDifficulty)
{
    DifficultyConfig* difficulty = DifficultyConfig::getInstance(DifficultyLevel::Easy);
    EXPECT_EQ(difficulty->getLevel(), DifficultyLevel::Easy);

    int easyAdd = difficulty->getMonsterHealthAddition();

    difficulty->testSetLevel(DifficultyLevel::Medium);
    int medAdd = difficulty->getMonsterHealthAddition();

    difficulty->testSetLevel(DifficultyLevel::Hard);
    int hardAdd = difficulty->getMonsterHealthAddition();
    EXPECT_TRUE(easyAdd < medAdd);
    EXPECT_TRUE(medAdd < hardAdd);
}

TEST(TestWeatherCardDeck, TestDeckHandling)
{
	WeatherCardDeck* weatherDeck = WeatherCardDeck::getInstance();
    DifficultyConfig* difficulty = DifficultyConfig::getInstance();

    vector<WeatherCard> deck = weatherDeck->testGetAllCardsInDeck();
    vector<int> cardsCount;
    for (int i = 0; i <= WeatherCard::end; ++i)
        cardsCount.push_back(0);
    for (auto card : deck)
    {
        cardsCount[card]++;
    }
    EXPECT_EQ(cardsCount[WeatherCard::Clean], difficulty->getWeatherCardCountClean());
    EXPECT_EQ(cardsCount[WeatherCard::Clowdy], difficulty->getWeatherCardCountClowdy());
    EXPECT_EQ(cardsCount[WeatherCard::Lightning], difficulty->getWeatherCardCountLightning());
    EXPECT_EQ(cardsCount[WeatherCard::Meteorite], difficulty->getWeatherCardCountMeteorite());
    EXPECT_EQ(cardsCount[WeatherCard::OzonHole], difficulty->getWeatherCardCountOzon());
    EXPECT_EQ(cardsCount[WeatherCard::Thunder], difficulty->getWeatherCardCountThunder());

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

    //just refill without shuffling
    weatherDeck->testFill();
    weatherDeck->print();
    deck.clear();
    deck = weatherDeck->testGetAllCardsInDeck();

    /*
    cout << "Check probabilities? 0 - no, 1 - yes" << endl;
    int toCheck = 0;
    cin >> toCheck;

    if (toCheck)
    {
        cout << "Game difficulty: " << (difficulty->getLevel() == DifficultyLevel::Easy ? "easy" : (difficulty->getLevel() == DifficultyLevel::Medium ? "medium" : "hard")) << endl;
        getProbability(deck, 3);
        getProbability(deck, 4);
        getProbability(deck, 5);
    }*/
}


bool isEqualVectors(const vector<WeatherCard>& left, const vector<WeatherCard>& right)
{
    for (int i = 0; i < left.size(); ++i)
    {
        if (left[i] != right[i])
        {
            return false;
        }
    }
    return true;
}

TEST(TestWeatherDesk, TestDeskHandling)
{
    const int deskSize = 5;
    WeatherDesk* desk = WeatherDesk::getInstance(deskSize);
    vector<WeatherCard> cardsToPush{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Lightning, WeatherCard::Meteorite, WeatherCard::OzonHole };
    desk->testFillTheDesk(cardsToPush, deskSize);
    vector<WeatherCard> cardsOnDesk = desk->testGetAllCardsInDesk();
    
    EXPECT_EQ(cardsOnDesk.size(), cardsToPush.size());
    EXPECT_TRUE(isEqualVectors(cardsOnDesk, cardsToPush));

    // test how new cards will be pushed to the desk
    vector<WeatherCard> newCards{ WeatherCard::Clean, WeatherCard::Clowdy };
    desk->putCardsOnDesk(newCards);
    cardsOnDesk = desk->testGetAllCardsInDesk();
    EXPECT_EQ(cardsOnDesk.size(), deskSize);
    EXPECT_TRUE(isEqualVectors(cardsOnDesk, { WeatherCard::Lightning, WeatherCard::Meteorite, WeatherCard::OzonHole, WeatherCard::Clean, WeatherCard::Clowdy }));

    // Damage test
    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Thunder };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::Null);
    }
    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::OzonHole };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::All);
    }
    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::OzonHole };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::One);
    }
    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clowdy, WeatherCard::Clean, WeatherCard::OzonHole, WeatherCard::Thunder };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::OzonHole) == WeatherDamage::Null);
    }

    //------------------
    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::Null);
    }
    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Thunder, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::Null);
    }
    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Lightning, WeatherCard::Clean, WeatherCard::Clean, WeatherCard::Clean };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::One);
    }

    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Clean, WeatherCard::Thunder, WeatherCard::Lightning, WeatherCard::Clean, WeatherCard::Clean };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::All);
    }

    {
        vector<WeatherCard> cardsOnDesk{ WeatherCard::Lightning, WeatherCard::Thunder, WeatherCard::Lightning, WeatherCard::Thunder, WeatherCard::Clean };
        desk->testFillTheDesk(cardsOnDesk, 5);
        EXPECT_TRUE(desk->getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::All);
    }
}