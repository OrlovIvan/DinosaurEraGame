#include "pch.h"
#include "Doctor.h"

void Doctor::useMedKit()
{
	int medKitIndex = this->Person::hasMedKit();
	if (medKitIndex != -1)
	{
		this->Person::useMedKit();
		m_inventory[medKitIndex] = Item(ItemName::medKit);
	}
}
