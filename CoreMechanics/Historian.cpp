#include "pch.h"
#include "Historian.h"
#include "Dices.h"

using namespace DicesNS;

// Historian cannot get 1 point on dices, so roll it until dices value will not consist 1 on each dice
unsigned Historian::hit()
{
	auto dicesPtr = Dices::getInstance();
	
	dicesPtr->rollDices();

	while (dicesPtr->getFirstDiceValue() == 1)
	{
		dicesPtr->rollOneDice(TheDice::first);
	}

	while (dicesPtr->getSecondDiceValue() == 1)
	{
		dicesPtr->rollOneDice(TheDice::second);
	}

	takeAction();
	return m_inventory.getWeaponInHandsPower() + dicesPtr->getFirstDiceValue() + dicesPtr->getSecondDiceValue();
}
