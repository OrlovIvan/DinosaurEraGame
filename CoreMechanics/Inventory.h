#pragma once
#include "Items.h"
#include <vector>

namespace InventoryNS
{
	constexpr int MAX_INVENTORY_COUNT = 6;
	constexpr unsigned COCCOON_PLACE = 2;

	class Inventory
	{
	public:
		Inventory();

		int useMedKit();
		bool takeItemToInventory(Item item);
		bool hasUmbrellaInHand() const;
		bool eatFood();

	private:
		int hasMedKit() const;
		bool hasCoccoon() const;
		bool hasFreeSpaceInInventory();
		int hasFood() const;

		std::vector<Item> m_inventory;
	};
}

