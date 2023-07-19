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

    // trying to take coccoon and food
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::cocoon)).getItemName() == ItemName::none);
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::food)).getItemName() == ItemName::none);
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::cocoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::food);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::none);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::none);
    }

    // swap umbrella and food
    EXPECT_TRUE(person->hasUmbrellaInHand());
    EXPECT_TRUE(person->swapItemsInInventory(1,3));
    EXPECT_FALSE(person->hasUmbrellaInHand());
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::food);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::cocoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::none);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::none);
    }
    EXPECT_TRUE(person->swapItemsInInventory(1, 3));

    // two items more to fill the inventory
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::medKit)).getItemName() == ItemName::none);
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::gun)).getItemName() == ItemName::none);
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::cocoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::food);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::medKit);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::gun);
    }

    // trying to add one more to the full inventory
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::bat)).getItemName() == ItemName::bat);

    person->useMedKit(); //use medKit, free slot #4 in inventory. Put telescope there
    EXPECT_TRUE(person->takeItemToInventory(Item(ItemName::telescope)).getItemName() == ItemName::none);
    {
        auto& inventory = person->getInventory();
        EXPECT_TRUE(inventory[0].getItemName() == ItemName::branch);
        EXPECT_TRUE(inventory[1].getItemName() == ItemName::umbrella);
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::cocoon);
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
        EXPECT_TRUE(inventory[2].getItemName() == ItemName::cocoon);
        EXPECT_TRUE(inventory[3].getItemName() == ItemName::detail);
        EXPECT_TRUE(inventory[4].getItemName() == ItemName::telescope);
        EXPECT_TRUE(inventory[5].getItemName() == ItemName::gun);
    }

    EXPECT_TRUE(person->dropItemFromInventory(3).getItemName() == ItemName::detail);
    EXPECT_TRUE(person->hasUmbrellaInHand());
    EXPECT_TRUE(person->dropItemFromInventory(1).getItemName() == ItemName::umbrella);
    EXPECT_FALSE(person->hasUmbrellaInHand());

    // trying to drop a cocoon with items inside it
    EXPECT_TRUE(person->dropItemFromInventory(2).getItemName() == ItemName::none);  //we cannot drop a cocoon until we have items inside it
    EXPECT_TRUE(person->dropItemFromInventory(5).getItemName() == ItemName::gun);
    EXPECT_TRUE(person->dropItemFromInventory(4).getItemName() == ItemName::telescope);
    EXPECT_TRUE(person->dropItemFromInventory(2).getItemName() == ItemName::cocoon);

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
    // testing weapons power in inventory
    InventoryNS::Inventory inventory;
    EXPECT_EQ(inventory.getWeaponInHandsPower(), 0);

    inventory.takeItemToInventory(Item(ItemName::detail));
    inventory.takeItemToInventory(Item(ItemName::food));
    EXPECT_EQ(inventory.getWeaponInHandsPower(), 0);

    inventory.takeItemToInventory(Item(ItemName::cocoon));
    inventory.takeItemToInventory(Item(ItemName::branch));
    inventory.takeItemToInventory(Item(ItemName::bat));
    inventory.takeItemToInventory(Item(ItemName::gun));
    EXPECT_EQ(inventory.getWeaponInHandsPower(), 0);

    inventory.dropItemFromInventory(InventoryNS::Hands::left);
    inventory.dropItemFromInventory(InventoryNS::Hands::right);
    inventory.takeItemToInventory(Item(ItemName::bat));
    inventory.takeItemToInventory(Item(ItemName::gun));
    EXPECT_EQ(inventory.getWeaponInHandsPower(), 5);

    inventory.dropItemFromInventory(InventoryNS::Hands::left);
    inventory.takeItemToInventory(Item(ItemName::food));
    EXPECT_EQ(inventory.getWeaponInHandsPower(), 3);

    inventory.dropItemFromInventory(InventoryNS::Hands::left);
    inventory.takeItemToInventory(Item(ItemName::gun));
    EXPECT_EQ(inventory.getWeaponInHandsPower(), 6);

    // test hit() method (weapon power + dices values)
    std::unique_ptr<Person> person(new Policeman);
    person->takeItemToInventory(Item(ItemName::branch));
    person->takeItemToInventory(Item(ItemName::branch));
    EXPECT_TRUE(person->hit() >= 2+2); // branch(1)+branch(1)+dices(at least 2)

    // Warning! This test case depends on random generated values, so may sometimes give wrong result when dice's values repeat
    auto hitVal1 = person->hit();
    auto hitVal2 = person->hit();
    if(hitVal1 == hitVal2)
        hitVal2 = person->hit();
    EXPECT_TRUE(hitVal1 != hitVal2);
}

TEST(TestPersonClass, TestActions)
{
    std::unique_ptr<Person> person(new Policeman);
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS);

    person->takeItemToInventory(Item(ItemName::branch));
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS-1);

    person->dropItemFromInventory(0);
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS - 2);

    person->hit();
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS - 3);
    person->hit();
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS - 4);

    person->addAction();
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS - 3);

    person->addAction(MAX_ACTIONS);
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS);

    person->stepDown();
    person->stepUp();
    person->stepLeft();
    person->stepRight();
    EXPECT_EQ(person->getActionsCount(), MAX_ACTIONS - 4);
}