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

using namespace std;

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;



class MockRummy : public Rummy {
public:
    MOCK_METHOD1(getDeck, int (std::vector<Card> & deck));
    MOCK_METHOD1(shuffle, void (std::vector<Card> & deck));
    MOCK_METHOD2(addPlayers, void (std::queue<Player*> 
  & players, int & playerCount));

    MOCK_METHOD3(deal, void (std::queue<std::vector<Card>> 
  & playersHands, std::vector<Card> & deck, int & playerCount));
    
    MOCK_METHOD2(fillBoard, void (std::vector< std::vector<Card>> & melds,   
    std::unordered_map<std::string, std::vector<Card>> & runs));

};

class MockPlayer : public Player {
public:
    MOCK_METHOD0(startGame, int ());
};

TEST (ModelTest, setupGame) {
    MockPlayer * player = new MockPlayer;
    MockRummy rummy;
    Model model(rummy, player);
    
    EXPECT_CALL(rummy, getDeck(_))
   .Times(1)
   .WillOnce(Return(52));

   EXPECT_CALL(rummy, shuffle(_))
   .Times(1);

    EXPECT_CALL(*player, startGame)
   .Times(1)
   .WillOnce(Return(4));

    EXPECT_CALL(rummy, addPlayers(_,_))
   .Times(1);

   EXPECT_CALL(rummy, deal(_,_,_))
   .Times(1);

    EXPECT_CALL(rummy, fillBoard(_,_))
   .Times(1);

    bool value = model.setupGame();

    EXPECT_EQ(value, 1);
    delete player;
}


TEST (ModelTest, rungGame) {
    MockPlayer * player = new MockPlayer;
    MockRummy rummy;
    Model model(rummy, player);
    
    EXPECT_CALL(rummy, getDeck(_))
   .Times(1)
   .WillOnce(Return(52));

   EXPECT_CALL(rummy, shuffle(_))
   .Times(1);

    EXPECT_CALL(*player, startGame)
   .Times(1)
   .WillOnce(Return(4));

    EXPECT_CALL(rummy, addPlayers(_,_))
   .Times(1);

   EXPECT_CALL(rummy, deal(_,_,_))
   .Times(1);

    EXPECT_CALL(rummy, fillBoard(_,_))
   .Times(1);

    bool value = model.setupGame();

    EXPECT_EQ(value, 1);
    delete player;
}
