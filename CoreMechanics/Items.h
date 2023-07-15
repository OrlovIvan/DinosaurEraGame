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

enum WeaponPower
{
	branch = 1,
	bat = 2,
	gun = 3
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

	unsigned getItemPower() const
	{
		if (m_itemName == ItemName::branch)
			return WeaponPower::branch;
		if(m_itemName == ItemName::bat)
			return WeaponPower::bat;
		if (m_itemName == ItemName::gun)
			return WeaponPower::gun;
		return 0;
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