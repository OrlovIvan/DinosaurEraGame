#pragma once
#include "Items.h"
#include <vector>

namespace InventoryNS
{
	constexpr int MAX_INVENTORY_COUNT = 6;
	constexpr unsigned COCCOON_PLACE = 2;

	enum Hands
	{
		left = 0,
		right = 1
	};

	class Inventory
	{
	public:
		Inventory();

		int useMedKit();
		Item takeItemToInventory(Item item, int forceTakeIndex = -1);
		Item dropItemFromInventory(unsigned index);
		bool hasUmbrellaInHand() const;
		bool eatFood();
		const std::vector<Item>& getInventory() const;
		unsigned getWeaponInHandsPower() const;

	private:
		int hasMedKit() const;
		bool hasCoccoon() const;
		int getFreeSpaceIndexInInventory();
		int hasFood() const;


		std::vector<Item> m_inventory;
	};
}

