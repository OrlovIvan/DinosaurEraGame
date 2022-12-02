#pragma once

#define METEORITE_BEGIN_LEVEL (2)
#define METEORITE_STRIKE_LEVEL (6)

class MeteoriteLevel
{
public:
	static MeteoriteLevel* getInstance()
	{
		if (!instance)
			instance = new MeteoriteLevel();
		return instance;
	}

	unsigned getMeteoriteLevel() const;
	bool incrementMeteoriteLevel();
	void decrementMeteoriteLevel();
	bool isGameOver() const;
private:
	friend class Test;
	MeteoriteLevel();

	void testSetClass(unsigned level, unsigned subLevel);
	void print() const;
	unsigned getSubLevel() const { return m_sublevel; }

	static MeteoriteLevel* instance;
	unsigned m_sublevel{0};
	unsigned m_meteoriteLevel{ METEORITE_BEGIN_LEVEL };
};

