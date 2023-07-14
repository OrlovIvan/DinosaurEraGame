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
		Item takeItemToInventory(Item item, int forceTakeIndex);
		Item dropItemFromInventory(unsigned index);
		bool hasUmbrellaInHand() const;
		bool eatFood();
		const std::vector<Item>& getInventory() const;

	private:
		int hasMedKit() const;
		bool hasCoccoon() const;
		int getFreeSpaceIndexInInventory();
		int hasFood() const;

		std::vector<Item> m_inventory;
	};
}

