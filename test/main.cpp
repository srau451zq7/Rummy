#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Card.h"
#include <string>
#include "Rummy.h"
#include "Model.h"
#include "Player.h"
#include "Computer.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}