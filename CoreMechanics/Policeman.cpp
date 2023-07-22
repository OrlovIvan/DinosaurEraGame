#include "pch.h"
#include "Policeman.h"

// Policeman hits a monster with +1 of attack if he has weapons at least in one hand
unsigned Policeman::hit()
{
	if (m_inventory.getWeaponInHandsPower() > 0)
		return Person::hit() + 1;
	return Person::hit();
}
