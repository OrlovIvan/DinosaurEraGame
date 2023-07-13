#pragma once

#include <vector>
#include "Items.h"
#include "Position.h"
#include "RandomGenerator.h"
#include "Inventory.h"

#define MAX_HEALTH (5)
#define MAX_ACTIONS (4)

using namespace positions;

enum Hands
{
	left = 0,
	right
};

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

	bool takeItemToInventory(Item item);

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

protected:
	unsigned int m_health{ MAX_HEALTH };
	bool m_isUnconscious{false};

	//unsigned int food{ 0 };
	unsigned m_actions{ MAX_ACTIONS };
	InventoryNS::Inventory m_inventory;
	
	Position m_position;
};

