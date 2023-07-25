#include <iostream>

#include "pch.h"
#include "Policeman.h"
#include "Doctor.h"
#include "Dices.h"

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

    policeman.takeItemToInventory(Item(ItemName::branch));
    checkHitValue(&policeman, policeman.hit()-1);

    policeman.takeItemToInventory(Item(ItemName::bat));
    checkHitValue(&policeman, policeman.hit() - 1);

    policeman.takeItemToInventory(Item(ItemName::cocoon));
    policeman.swapItemsInInventory(InventoryNS::InventoryPlaces::leftHand, InventoryNS::InventoryPlaces::cocoonCell_1);
    policeman.swapItemsInInventory(InventoryNS::InventoryPlaces::rightHand, InventoryNS::InventoryPlaces::cocoonCell_2);
    checkHitValue(&policeman, policeman.hit());
}

TEST(TestCharacters, TestDoctor)
{
    Doctor doctor;

    EXPECT_TRUE(doctor.takeItemToInventory(Item(ItemName::medKit)).getItemName() == ItemName::none);
    doctor.useMedKit();
    auto& inventory = doctor.getInventory();
    EXPECT_TRUE(inventory[InventoryNS::InventoryPlaces::leftHand].getItemName() == ItemName::medKit);

    doctor.takeItemToInventory(Item(ItemName::cocoon));
    doctor.swapItemsInInventory(InventoryNS::InventoryPlaces::leftHand, InventoryNS::InventoryPlaces::cocoonCell_1);
    doctor.takeItemToInventory(Item(ItemName::branch));
    doctor.takeItemToInventory(Item(ItemName::gun));

    checkHitValue(&doctor, doctor.hit());
}
