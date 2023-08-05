#include "pch.h"
#include "Historian.h"
#include "Dices.h"

using namespace DicesNS;

// Historian cannot get 1 point on dices, so roll it until dices value will not consist 1 on each dice
unsigned Historian::hit()
{
	Dices::getInstance()->rollDices();

	while (Dices::getInstance()->getFirstDiceValue() == 1)
	{
		Dices::getInstance()->rollOneDice(TheDice::first);
	}

	while (Dices::getInstance()->getSecondDiceValue() == 1)
	{
		Dices::getInstance()->rollOneDice(TheDice::second);
	}

	takeAction();
	return m_inventory.getWeaponInHandsPower() + Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
}
