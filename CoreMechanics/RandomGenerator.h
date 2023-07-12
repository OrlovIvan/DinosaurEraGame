#pragma once

class RandomGenerator
{
public:
	RandomGenerator() {};
	~RandomGenerator() { }
	unsigned getRandomValue(int min, int max);
};
