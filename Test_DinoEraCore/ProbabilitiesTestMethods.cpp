#include <iostream>
#include "pch.h"
#include <vector>
#include "ProbabilitiesTestMethods.h"
#include "WeatherDesk.h"

using namespace std;

long long getCount(int n, int k)
{
    long long count = 0;
    int factK = 1;
    for (int i = 1; i <= k; ++i)
        factK *= i;

    long partFactN = 1;
    for (int i = n - k + 1; i <= n; ++i)
        partFactN *= i;

    return partFactN / factK;
}

enum
{
    no = 0,
    ozonOne,
    ozonAll,
    lightOne,
    lightAll
};

void compute(vector<int>& counts, const vector<WeatherCard>& deck, int cardsOnDesk, vector<WeatherCard>& vec)
{
    WeatherDesk* desk = WeatherDesk::getInstance();
    WeatherDamage damage;
    int meteoriteLevel = cardsOnDesk - 1;
    desk->testFillTheDesk(vec, meteoriteLevel);
    damage = desk->getDamageFromWeather(WeatherCard::OzonHole);

    if (damage == WeatherDamage::Null && desk->getDamageFromWeather(WeatherCard::Lightning) == WeatherDamage::Null)
        counts[no]++;

    switch (damage)
    {
    case WeatherDamage::Null:
        //counts[no]++;
        break;
    case WeatherDamage::One:
        counts[ozonOne]++;
        break;
    case WeatherDamage::All:
        counts[ozonAll]++;
        break;
    }

    damage = desk->getDamageFromWeather(WeatherCard::Lightning);
    switch (damage)
    {
    case WeatherDamage::Null:
        //counts[no]++;
        break;
    case WeatherDamage::One:
        counts[lightOne]++;
        break;
    case WeatherDamage::All:
        counts[lightAll]++;
        break;
    }
}

void getProbability(const vector<WeatherCard>& deck, int cardsOnDesk)
{
    vector<int> counts{0, 0, 0, 0, 0};
    long long caseCount = getCount(deck.size(), cardsOnDesk);

    WeatherDesk* desk = WeatherDesk::getInstance(3);
    vector<WeatherCard> vec;
    for (int i = 0;i < cardsOnDesk; ++i)
        vec.push_back(WeatherCard::Clean);

    const int size = deck.size();


    for (int i = 0; i < size; ++i)
    {
        vec[0] = deck[i];
        for (int j = i + 1; j < size; ++j)
        {
            vec[1] = deck[j];
            for (int k = j + 1; k < size; ++k)
            {
                vec[2] = deck[k];
                if (cardsOnDesk > 3)
                {
                    for (int m = k + 1; m < size; ++m)
                    {
                        vec[3] = deck[m];
                        if (cardsOnDesk > 4)
                        {
                            for (int b = m + 1; b < size; ++b)
                            {
                                vec[4] = deck[b];
                                compute(counts, deck, cardsOnDesk, vec);
                            }
                        }
                        else
                        {
                            compute(counts, deck, cardsOnDesk, vec);
                        }
                    }
                }
                else
                {
                    compute(counts, deck, cardsOnDesk, vec);
                }
            }
        }
    }

    cout << endl;
    cout << "Damage cases count for " << cardsOnDesk << " cards on desk: " << caseCount << endl;
    for (int i = 0; i < counts.size(); ++i)
    {
        switch (i)
        {
        case no:
            cout << "No damage: ";
            break;
        case ozonOne:
            cout << "OzonOne damage: ";
            break;
        case ozonAll:
            cout << "OzonAll damage: ";
            break;
        case lightOne:
            cout << "LightningOne damage: ";
            break;
        case lightAll:
            cout << "LightningAll damage: ";
            break;
        }
        cout << (double)counts[i] / (double)caseCount * 100 << "%" << endl;
    }
}