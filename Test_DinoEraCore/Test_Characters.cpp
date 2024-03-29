#include <iostream>

#include "pch.h"
#include "Dices.h"
#include "Luck.h"
#include "Policeman.h"
#include "Doctor.h"
#include "Astronomer.h"
#include "Historian.h"

using namespace DicesNS;

void checkHitValue(Person* person, unsigned expectedHitVal)
{
    Dices* dices = Dices::getInstance();
    auto& inventory = person->getInventory();
    EXPECT_EQ(dices->getFirstDiceValue() + dices->getSecondDiceValue() +
            inventory[InventoryNS::InventoryPlaces::leftHand].getItemPower() +
            inventory[InventoryNS::InventoryPlaces::rightHand].getItemPower(), expectedHitVal);
}

TEST(TestCharacters, TestPoliceman)
{
    Policeman policeman;
    checkHitValue(&policeman, policeman.hit());

    policeman.takeItemToInventory(Item(ItemName::stick));
    checkHitValue(&policeman, policeman.hit()-1);

    policeman.takeItemToInventory(Item(ItemName::bat));
    checkHitValue(&policeman, policeman.hit() - 1);

    policeman.takeItemToInventory(Item(ItemName::cocoon));
    policeman.swapItemsInInventory(InventoryNS::InventoryPlaces::leftHand, InventoryNS::InventoryPlaces::cocoonCell_1);
    policeman.swapItemsInInventory(InventoryNS::InventoryPlaces::rightHand, InventoryNS::InventoryPlaces::cocoonCell_2);
    checkHitValue(&policeman, policeman.hit());

    EXPECT_FALSE(policeman.getLuck().isThunderSafe());
}

TEST(TestCharacters, TestDoctor)
{
    Doctor doctor;

    EXPECT_TRUE(doctor.takeItemToInventory(Item(ItemName::medKit)).getItemName() == ItemName::none);
    doctor.useMedKit();
    {
        auto& inventory = doctor.getInventory();
        EXPECT_TRUE(inventory[InventoryNS::InventoryPlaces::leftHand].getItemName() == ItemName::medKit);
    }

    doctor.takeItemToInventory(Item(ItemName::cocoon));
    doctor.swapItemsInInventory(InventoryNS::InventoryPlaces::leftHand, InventoryNS::InventoryPlaces::cocoonCell_1);
    doctor.takeItemToInventory(Item(ItemName::stick));
    doctor.takeItemToInventory(Item(ItemName::gun));

    checkHitValue(&doctor, doctor.hit());

    doctor.getHit();
    EXPECT_EQ(doctor.getHealth(), MAX_HEALTH-1);
    doctor.useMedKit();
    EXPECT_EQ(doctor.getHealth(), MAX_HEALTH);
    {
        auto& inventory = doctor.getInventory();
        EXPECT_TRUE(inventory[InventoryNS::InventoryPlaces::cocoonCell_1].getItemName() == ItemName::medKit);
    }

    EXPECT_FALSE(doctor.getLuck().isThunderSafe());
}

TEST(TestCharacters, TestAstronomer)
{
    Astronomer astronomer;

    auto luck = astronomer.getLuck();
    EXPECT_TRUE(luck.isThunderSafe());

    auto lightningLuck = luck.getLightningLuck();
    auto dicesVal = Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
    EXPECT_TRUE(lightningLuck > dicesVal);

    auto ozonLuck = luck.getOzonLuck();
    dicesVal = Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
    EXPECT_TRUE(ozonLuck == dicesVal);
}

TEST(TestCharacters, TestHistorian)
{
    Historian historian;

    int count = 20;
    while (count--)
    {
        historian.hit();
        EXPECT_TRUE(Dices::getInstance()->getFirstDiceValue() != 1);
        EXPECT_TRUE(Dices::getInstance()->getSecondDiceValue() != 1);
    }

    EXPECT_FALSE(historian.getLuck().isThunderSafe());
}