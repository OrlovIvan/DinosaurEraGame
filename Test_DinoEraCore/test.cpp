#include "pch.h"
#include "MeteoriteLevel.h"
#include <iostream>

using namespace std;

TEST(TestMeteoriteLevel, TestLevelHandling)
{
  cout << "Meteorite test." << endl;
  MeteoriteLevel* metLevel = MeteoriteLevel::getInstance();

  metLevel->incrementMeteoriteLevel();
  metLevel->incrementMeteoriteLevel();
  metLevel->incrementMeteoriteLevel();
  EXPECT_EQ(metLevel->getMeteoriteLevel(), 3);

  metLevel->decrementMeteoriteLevel();
  EXPECT_EQ(metLevel->getMeteoriteLevel(), 2);

  metLevel->incrementMeteoriteLevel(); // make the meteorite level equal to 3
  for (int i = 0; metLevel->getMeteoriteLevel() == 6; ++i)
  {
	  metLevel->incrementMeteoriteLevel();
  }
  EXPECT_TRUE(metLevel->isGameOver());
}