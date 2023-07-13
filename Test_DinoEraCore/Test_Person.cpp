#include <iostream>

#include "pch.h"
#include "Person.h"
#include "Policeman.h"

TEST(TestPersonClass, TestHealth)
{
    std::unique_ptr<Person> person(new Policeman());

    EXPECT_EQ(person->getHealth(), MAX_HEALTH);
    person->getHit();
    EXPECT_EQ(person->getHealth(), MAX_HEALTH - 1);
    person->getHit();
    person->getHit();
    person->getHit();
    person->getHit();
    EXPECT_EQ(person->getHealth(), 0);
    EXPECT_TRUE(person->isUnconscious());
    person->awake();
    EXPECT_FALSE(person->isUnconscious());
    EXPECT_EQ(person->getHealth(), 1);

    person->useMedKit();
    EXPECT_EQ(person->getHealth(), 1);
    person->takeItemToInventory(Item(ItemName::medKit));
    person->useMedKit();
    EXPECT_EQ(person->getHealth(), MAX_HEALTH);

    person->getHit();
    person->useMedKit();
    EXPECT_EQ(person->getHealth(), MAX_HEALTH - 1);
}

TEST(TestPersonClass, TestPositioning)
{
    std::unique_ptr<Person> person(new Policeman());

    EXPECT_EQ(person->getPosition().x, 0);
    EXPECT_EQ(person->getPosition().y, 0);

    EXPECT_TRUE(person->stepDown());
    EXPECT_TRUE(person->stepRight());
    EXPECT_EQ(person->getPosition().x, 1);
    EXPECT_EQ(person->getPosition().y, -1);

    person->stepUp();
    person->stepLeft();
    EXPECT_EQ(person->getPosition().x, 0);
    EXPECT_EQ(person->getPosition().y, 0);

    for (int i = 0;i <= positions::Max_X;++i)
    {
        person->stepUp();
        person->stepRight();
    }
    EXPECT_EQ(person->getPosition().x, Max_X);
    EXPECT_EQ(person->getPosition().y, Max_Y);
    EXPECT_FALSE(person->stepUp());
    EXPECT_FALSE(person->stepRight());
    EXPECT_EQ(person->getPosition().x, Max_X);
    EXPECT_EQ(person->getPosition().y, Max_Y);

    for (int i = 0;i <= positions::Max_X;++i)
    {
        person->stepDown();
        person->stepLeft();
    }
    for (int i = 0;i <= -positions::Min_X;++i)
    {
        person->stepDown();
        person->stepLeft();
    }
    EXPECT_EQ(person->getPosition().x, Min_X);
    EXPECT_EQ(person->getPosition().y, Min_Y);
    EXPECT_FALSE(person->stepDown());
    EXPECT_FALSE(person->stepLeft());
    EXPECT_EQ(person->getPosition().x, Min_X);
    EXPECT_EQ(person->getPosition().y, Min_Y);
}

TEST(TestPersonClass, TestInventory)
{
    std::unique_ptr<Person> person(new Policeman);
    person->takeItemToInventory(Item(ItemName::medKit));
}

TEST(TestPersonClass, TestWeapons)
{
    std::unique_ptr<Person> person(new Policeman);
    person->takeItemToInventory(Item(ItemName::branch));
}