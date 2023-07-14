#pragma once

#include "Position.h"

using namespace positions;

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
	Item(const Item& src)
	{
		m_itemName = src.m_itemName;
		m_position = src.m_position;
	}

	ItemName getItemName() const
	{
		return m_itemName;
	}

	void operator=(const Item& src)
	{
		m_itemName = src.m_itemName;
		m_position = src.m_position;
	}

private:
	ItemName m_itemName;
	Position m_position;
};