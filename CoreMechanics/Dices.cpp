#include "pch.h"
#include "Dices.h"

Dices* Dices::m_instance = nullptr;

Dices::Dices()
{
	tossDices();
}

void Dices::tossDices()
{
	m_firstDice = randGen.getRandomValue(dice_min, dice_max);
	m_secondDice = randGen.getRandomValue(dice_min, dice_max);
}
