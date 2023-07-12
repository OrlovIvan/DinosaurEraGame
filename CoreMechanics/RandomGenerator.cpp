#include "pch.h"
#include "RandomGenerator.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/chrono/chrono.hpp>

boost::random::mt19937 gen;

unsigned RandomGenerator::getRandomValue(int min, int max)
{
    auto time1 = boost::chrono::system_clock::now();
    
    boost::random::uniform_int_distribution<> dist(min, max);
    ::Sleep(1);
    
    boost::chrono::nanoseconds duration = boost::chrono::system_clock::now() - time1;
    unsigned dummyRounds = duration.count()/100000;

    while (dummyRounds--)
    {
        dist(gen);
    }
    
    return dist(gen);
}