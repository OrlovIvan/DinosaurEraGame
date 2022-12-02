#include "Test.h"
#include <iostream>
#include "MeteoriteLevel.h"

using namespace std;

void Test::testMeteoriteLevel()
{
	cout << "Meteorite test." << endl;
	MeteoriteLevel* metLevel = MeteoriteLevel::getInstance();
	{
		cout << "SubLevel inc 0 -> 1: ";
		metLevel->testSetClass(2, 0);
		metLevel->incrementMeteoriteLevel();
		if (metLevel->testGetSubLevel() == 1)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

	{
		cout << "Level inc sub 2 -> 0, met 2 -> 3: ";
		metLevel->testSetClass(2, 2);
		metLevel->incrementMeteoriteLevel();
		if (metLevel->testGetSubLevel() == 0 && metLevel->getMeteoriteLevel() == 3)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

	{
		cout << "SubLevel dec 2 -> 1: ";
		metLevel->testSetClass(2, 2);
		metLevel->decrementMeteoriteLevel();
		if (metLevel->testGetSubLevel() == 1)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

	{
		cout << "Dec sub 0 -> 2, met 3 -> 1: ";
		metLevel->testSetClass(3, 0);
		metLevel->decrementMeteoriteLevel();
		if (metLevel->testGetSubLevel() == 2 && metLevel->getMeteoriteLevel() == 2)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

	{
		cout << "IsGameOver: ";
		metLevel->testSetClass(5, 2);
		metLevel->incrementMeteoriteLevel();
		if (metLevel->isGameOver())
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
}
