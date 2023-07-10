#include "pch.h"
#include "RandomGenerator.h"
#include <random>

RandomGenerator* RandomGenerator::m_instance = nullptr;

RandomGenerator::RandomGenerator()
{
	makeRandomValues();
}

void RandomGenerator::makeRandomValues()
{
	m_firstDice = rand() % 6 + 1;
	m_secondDice = rand() % 6 + 1;
}