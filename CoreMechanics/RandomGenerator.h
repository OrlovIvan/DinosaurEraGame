#pragma once

class RandomGenerator
{
	~RandomGenerator() { delete m_instance; }
public:
	static RandomGenerator* getInstance()
	{
		if (!m_instance)
		{
			m_instance = new RandomGenerator();
		}
		return m_instance;
	}

	void makeRandomValues();
	unsigned getFirstDiceValue() const { return m_firstDice; }
	unsigned getSecondDiceValue() const { return m_secondDice; }
private:
	RandomGenerator();

	static RandomGenerator* m_instance;

	unsigned m_firstDice{ 0 };
	unsigned m_secondDice{ 0 };
};
