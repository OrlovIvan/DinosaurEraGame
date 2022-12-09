#pragma once

#define MAX_HEALTH (5)
#define MAX_ACTIONS (4)

struct Position
{
	int x{0};
	int y{0};
};

class Person
{
public:
	Person() {}
	virtual ~Person() {}

	void damage();
	void awake();
	virtual void useMedKit();
	void eatFood();
	void takeFood();
	void takeMedKit();
	void takeUmbrella();
	int getHealth() const;

	bool hasUmbrella() { return m_hasUmbrella; }
	virtual bool isThunderSafe() { return false; }
	virtual int luck() { return 0; }

	bool stepUp();
	bool stepDown();
	bool stepRight();
	bool stepLeft();

protected:
	unsigned int m_health{ MAX_HEALTH };
	bool m_hasUmbrella{false};
	bool m_hasMedKit{false};
	bool m_isUnconscious{false};
	unsigned int food{ 0 };
	unsigned m_actions{ MAX_ACTIONS };

	Position m_position;
};

