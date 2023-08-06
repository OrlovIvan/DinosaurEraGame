#include "pch.h"
#include "Dices.h"
#include "Luck.h"

using namespace LuckNS;
using namespace DicesNS;

unsigned Luck::getLightningLuck() const
{
	Dices::getInstance()->rollDices();
	return m_lightningLuck + Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
}

unsigned Luck::getOzonLuck() const
{
	Dices::getInstance()->rollDices();
	return m_ozonLuck + Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
}

bool LuckNS::Luck::isThunderSafe() const
{
	return m_isThunderSafe;
}
