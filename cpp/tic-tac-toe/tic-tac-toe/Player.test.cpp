#include "Player.h"
#include <string>
#include <gtest/gtest.h>

TEST(PlayerTests, PlayerGetNameTest){
    string name = "Avinash";
    Player player(name);
    EXPECT_EQ(name, player.GetName());
}