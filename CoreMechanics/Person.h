#pragma once

#include <vector>
#include "Items.h"
#include "Position.h"

#define MAX_HEALTH (5)
#define MAX_ACTIONS (4)
#define COCCOON_PLACE (2)

constexpr int MAX_INVENTORY_COUNT = 6;

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

	void hit();
	void getHit();
	bool isUnconscious() const { return m_isUnconscious; };
	void awake();

	virtual void useMedKit();

	bool takeItemToInventory(Item item);

	void eatFood();
	void takeFood();

	void takeUmbrella();

	int getHealth() const;

	bool hasUmbrellaInHand() const;
	virtual bool isThunderSafe() { return false; }
	virtual int luck() { return 0; }
	bool hasFreeSpaceInInventory();

	bool stepUp();
	bool stepDown();
	bool stepRight();
	bool stepLeft();

	Position getPosition() const { return m_position; }

protected:
	int hasMedKit() const;
	bool hasCoccoon() const;

	unsigned int m_health{ MAX_HEALTH };
	bool m_isUnconscious{false};
	unsigned int food{ 0 };
	unsigned m_actions{ MAX_ACTIONS };
	std::vector<Item> m_inventory;
	
	Position m_position;
};

