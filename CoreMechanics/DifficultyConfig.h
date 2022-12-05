#pragma once

enum class DifficultyLevel
{
	Easy = 0,
	Medium,
	Hard
};

class DifficultyConfig
{
public:
	static DifficultyConfig* getInstance(DifficultyLevel level = DifficultyLevel::Medium)
	{
		if (!instance)
		{
			instance = new DifficultyConfig(level);
		}
		return instance;
	}

	DifficultyLevel getLevel() const
	{
		return m_level;
	}

	unsigned getWeatherCardCountClean() const;
	unsigned getWeatherCardCountClowdy() const;
	unsigned getWeatherCardCountThunder() const;
	unsigned getWeatherCardCountOzon() const;
	unsigned getWeatherCardCountLightning() const;
	unsigned getWeatherCardCountMeteorite() const;

	unsigned getMonsterHealthAddition() const;

	void testSetLevel(DifficultyLevel level)
	{
		m_level = level;
	}
private:
	DifficultyConfig(DifficultyLevel level) : m_level(level) {}

	static DifficultyConfig* instance;

	DifficultyLevel m_level;
};

