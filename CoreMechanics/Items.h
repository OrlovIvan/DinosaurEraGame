#pragma once

#include "Position.h"

enum class ItemName
{
	none = -1,
	food = 0,
	medKit,
	umbrella,
	coccoon,
	detail,
	telescope,

	branch,
	bat,
	gun
};

class Item
{
public:
	Item() = delete;
	Item(ItemName itemName) : m_itemName(itemName) {}

	ItemName getItemName() const
	{
		return m_itemName;
	}

private:
	ItemName m_itemName;
	Position m_position;
};