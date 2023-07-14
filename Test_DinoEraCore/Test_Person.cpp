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
    person->takeItemToInventory(Item(ItemName::branch));
    person->takeItemToInventory(Item(ItemName::umbrella));
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::branch)).getItemName() == ItemName::branch );
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::none);
    }

    // trying to take coccoon
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::coccoon)).getItemName() == ItemName::none);
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::food)).getItemName() == ItemName::none);
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::coccoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::food);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::none);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::none);
    }

    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::medKit)).getItemName() == ItemName::none);
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::gun)).getItemName() == ItemName::none);
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::coccoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::food);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::medKit);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::gun);
    }

    person->useMedKit(); //use medKit, free slot #4 in inventory. Put telescope there
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::telescope)).getItemName() == ItemName::none);
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::coccoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::food);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::telescope);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::gun);
    }

    // testing swapping a new taken item to the one in inventory
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::detail), 3).getItemName() == ItemName::food);
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::coccoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::detail);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::telescope);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::gun);
    }

    EXPECT_TRUE(person->dropItemFromInventory(3).getItemName() == ItemName::detail);
    EXPECT_TRUE(person->dropItemFromInventory(1).getItemName() == ItemName::umbrella);
    EXPECT_TRUE(person->dropItemFromInventory(2).getItemName() == ItemName::coccoon);
    EXPECT_TRUE(person->dropItemFromInventory(5).getItemName() == ItemName::gun);
    EXPECT_TRUE(person->dropItemFromInventory(4).getItemName() == ItemName::telescope);
    EXPECT_TRUE(person->dropItemFromInventory(0).getItemName() == ItemName::branch);
    {
        auto& inventory = person->getInventory();
        for (int i = 0;i < InventoryNS::MAX_INVENTORY_COUNT;++i)
        {
            EXPECT_TRUE(inventory[i].getItemName() == ItemName::none);
        }
    }
}

TEST(TestPersonClass, TestWeapons)
{
    std::unique_ptr<Person> person(new Policeman);
    person->takeItemToInventory(Item(ItemName::branch));
}