#pragma once
#include "RandomGenerator.h"

const unsigned dice_min = 1;
const unsigned dice_max = 6;

namespace DicesNS
{
	enum TheDice
	{
		first,
		second
	};

	class Dices
	{
		~Dices() { delete m_instance; }
	public:
		static Dices* getInstance()
		{
			if (!m_instance)
			{
				m_instance = new Dices();
			}
			return m_instance;
		}

		void rollDices();
		void rollOneDice(TheDice dice);
		unsigned getFirstDiceValue() const { return m_firstDice; }
		unsigned getSecondDiceValue() const { return m_secondDice; }
	private:
		Dices();

		RandomGenerator randGen;
		static Dices* m_instance;

		unsigned m_firstDice{ 0 };
		unsigned m_secondDice{ 0 };
	};
}