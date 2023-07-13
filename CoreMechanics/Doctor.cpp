#include "pch.h"
#include "Doctor.h"

int Doctor::useMedKit()
{
	int medKitIndex = this->Person::useMedKit();
	if (medKitIndex != -1)
	{
		this->Person::takeItemToInventory(Item(ItemName::medKit));
	}
	return medKitIndex;
}
