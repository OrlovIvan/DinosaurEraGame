#include <iostream>

#include "pch.h"
#include "Dices.h"
#include "Luck.h"

using namespace DicesNS;

TEST(TestLuck, TestLuckClass)
{
    {
        LuckNS::Luck luck(false);

        EXPECT_FALSE(luck.isThunderSafe());

        auto lightningLuck = luck.getLightningLuck();
        auto dicesVal = Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
        EXPECT_TRUE(lightningLuck == dicesVal);

        auto ozonLuck = luck.getOzonLuck();
        dicesVal = Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
        EXPECT_TRUE(ozonLuck == dicesVal);
    }

    {
        LuckNS::Luck luck(true, 1, 2);
        EXPECT_TRUE(luck.isThunderSafe());

        auto lightningLuck = luck.getLightningLuck();
        auto dicesVal = Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
        EXPECT_TRUE(lightningLuck - dicesVal == 1);

        auto ozonLuck = luck.getOzonLuck();
        dicesVal = Dices::getInstance()->getFirstDiceValue() + Dices::getInstance()->getSecondDiceValue();
        EXPECT_TRUE(ozonLuck - dicesVal == 2);
    }
}