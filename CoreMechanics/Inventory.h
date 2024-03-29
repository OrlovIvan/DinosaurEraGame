#pragma once
#include "Items.h"
#include <vector>

namespace InventoryNS
{
	constexpr int MAX_INVENTORY_COUNT = 6;
	constexpr unsigned COCCOON_PLACE = 2;

	enum InventoryPlaces
	{
		leftHand = 0,
		rightHand = 1,
		cocoonPlace = 2,
		cocoonCell_1 = 3,
		cocoonCell_2,
		cocoonCell_3
	};

	class Inventory
	{
	public:
		Inventory();

		int useMedKit();
		Item takeItemToInventory(Item item, int forceTakeIndex = -1);
		Item dropItemFromInventory(unsigned index);
		bool swapItemsInInventory(unsigned index1, unsigned index2);
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

