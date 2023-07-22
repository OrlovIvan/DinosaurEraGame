#include <iostream>

#include "pch.h"
#include "Policeman.h"
#include "Doctor.h"
#include "Dices.h"

TEST(TestCharacters, TestPoliceman)
{
    Policeman policeman;
    Dices* dices = Dices::getInstance();
    auto hitValue = policeman.hit();
    EXPECT_EQ(dices->getFirstDiceValue() + dices->getSecondDiceValue(), hitValue);

    policeman.takeItemToInventory(Item(ItemName::branch));
    hitValue = policeman.hit();
    {
        auto& inventory = policeman.getInventory();
        EXPECT_EQ(dices->getFirstDiceValue() + dices->getSecondDiceValue() + inventory[InventoryNS::Hands::left].getItemPower() + inventory[InventoryNS::Hands::right].getItemPower(), hitValue - 1);
    }
    policeman.takeItemToInventory(Item(ItemName::bat));
    hitValue = policeman.hit();
    {
        auto& inventory = policeman.getInventory();
        EXPECT_EQ(dices->getFirstDiceValue() + dices->getSecondDiceValue() + inventory[InventoryNS::Hands::left].getItemPower() + inventory[InventoryNS::Hands::right].getItemPower(), hitValue - 1);
    }

    policeman.takeItemToInventory(Item(ItemName::cocoon));
    policeman.swapItemsInInventory(InventoryNS::Hands::left, 3);
    policeman.swapItemsInInventory(InventoryNS::Hands::right, 4);
    hitValue = policeman.hit();
    {
        auto& inventory = policeman.getInventory();
        EXPECT_EQ(dices->getFirstDiceValue() + dices->getSecondDiceValue() + inventory[InventoryNS::Hands::left].getItemPower() + inventory[InventoryNS::Hands::right].getItemPower(), hitValue);
    }
}

TEST(TestCharacters, TestDoctor)
{
    /*std::unique_ptr<Person> person(new Policeman());

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
    EXPECT_EQ(person->getPosition().y, Min_Y);*/
}
