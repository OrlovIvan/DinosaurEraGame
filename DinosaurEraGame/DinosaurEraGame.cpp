// DinosaurEraGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Astronomer.h"
#include "Doctor.h"
#include "Thief.h"
#include "Inventor.h"
#include "Policeman.h"
#include "Historian.h"
#include "WeatherDeck.h"
#include "Test.h"

using namespace std;
void testWeatherDesk();

int main()
{
    Test test;
    test.testMeteoriteLevel();


    WeatherCardDeck* weatherDeck = WeatherCardDeck::getInstance();
    weatherDeck->print();

    cout << "*****Make a weather turn" << endl;
    weatherDeck->turn();
    weatherDeck->print();

    cout << "*****Make a weather turn" << endl;
    weatherDeck->turn();
    weatherDeck->print();

    cout << "*****Make a weather turn" << endl;
    weatherDeck->turn();
    weatherDeck->print();

    testWeatherDesk();

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
        
    while (weatherDeck->getMeteoriteLevel() != 6)
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
    }
}

void testWeatherDesk()
{
    cout << "***** Test weather damage *****" << endl;
    
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
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
