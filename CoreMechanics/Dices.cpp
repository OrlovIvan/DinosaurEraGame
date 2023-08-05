#include "pch.h"
#include "Dices.h"

using namespace DicesNS;

Dices* Dices::m_instance = nullptr;

Dices::Dices()
{
	rollDices();
}

void Dices::rollDices()
{
	rollOneDice(TheDice::first);
	rollOneDice(TheDice::second);
}

void DicesNS::Dices::rollOneDice(TheDice dice)
{
	switch (dice)
	{
	case first:
		m_firstDice = randGen.getRandomValue(dice_min, dice_max);
		break;
	case second:
		m_secondDice = randGen.getRandomValue(dice_min, dice_max);
		break;
	default: break;
	}
}
