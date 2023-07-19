#pragma once

#include <vector>
#include "Items.h"
#include "Position.h"
#include "Inventory.h"

#define MAX_HEALTH (5)
#define MAX_ACTIONS (4)

using namespace positions;

class Person
{
public:
	Person();
	virtual ~Person() {}

	virtual unsigned hit();
	void getHit();
	bool isUnconscious() const { return m_isUnconscious; };
	void awake();

	virtual int useMedKit();

	Item takeItemToInventory(Item item, int forceTakeIndex = -1);
	Item dropItemFromInventory(unsigned index);
	bool swapItemsInInventory(unsigned index1, unsigned index2);
	const std::vector<Item>& getInventory() const;

	void eatFood();

	int getHealth() const;

	bool hasUmbrellaInHand() const;
	virtual bool isThunderSafe() { return false; }
	virtual int luck() { return 0; }

	bool stepUp();
	bool stepDown();
	bool stepRight();
	bool stepLeft();

	Position getPosition() const { return m_position; }
	unsigned getActionsCount() const { return m_actions; }
	void addAction(unsigned count = 1);

protected:
	void takeAction();

	unsigned int m_health{ MAX_HEALTH };
	bool m_isUnconscious{false};

	//unsigned int food{ 0 };
	unsigned m_actions{ MAX_ACTIONS };
	InventoryNS::Inventory m_inventory;
	
	Position m_position;
};

