#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <unordered_set>
#include "Card.h"
#include "Rummy.h"
#include "Player.h"
#include <Computer.h>
#include "Model.h"

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


TEST (RummyTest, getDeck) {
  Rummy r;
  std::vector<Card> deck;
  std::unordered_set<std::string> hashCards;
  std::string temp;
  
  ASSERT_EQ(r.getDeck(deck), 52);

  for (int i = 0; i < deck.size(); i++) {
    hashCards.insert(temp = deck[i].value + deck[i].suit);
  }
  EXPECT_EQ(hashCards.size(), 52);
}

TEST (RummyTest, shuffle) {
  Rummy r;
  std::vector<Card> deck;
  bool flag = false;
  ASSERT_EQ(r.getDeck(deck), 52);
  for (int i = 0; i < 52; i++) {
    if (deck[i].value_ != deck[i+1].value_) {
      flag = true;
      break;
    }
  }
  EXPECT_TRUE(flag);
}

TEST (RummyTest, addPlayer) {
    std::queue<Player*> players;
    int playerCount = 4;
    Rummy r;
    r.addPlayers(players, playerCount);
    EXPECT_EQ(playerCount, players.size());
}

TEST (RummyTest, deal) {
    std::queue<std::vector<Card>> playersHands;
    int playerCount = 4;
    std::vector<Card> deck;
    Rummy r;
    r.getDeck(deck);
    r.deal(playersHands, deck, playerCount);
    deck = playersHands.back();
    EXPECT_EQ(7, deck.size());
}



TEST (RummyTest, fillBoard) {
  MockPlayer* ptr = new MockPlayer;
  Rummy r;
  Model m(r, ptr);
  m.setupGame();

  auto x = m.runs.find("Spades");
  EXPECT_EQ(x->second.size(),13);

  x = m.runs.find("Hearts");
  EXPECT_EQ(x->second.size(),13);

  x = m.runs.find("Diamonds");
  EXPECT_EQ(x->second.size(),13);

  x = m.runs.find("Clubs");
  EXPECT_EQ(x->second.size(),13);
  delete ptr;
}

TEST (RummyTest, sort) {
  std::vector<Card> temp;
  Rummy r;
  bool flag = true;
  temp.push_back({"Spades", "5", 5, 0});
  temp.push_back({"Spades", "1", 1, 0});
  temp.push_back({"Spades", "4", 4, 0});
  temp.push_back({"Spades", "9", 9, 0});
  r.sort(temp);
    for (int i = 0; i < temp.size() - 1; i++)
      if (temp[i].value_ > temp[i+1].value_)
        flag = false;
    EXPECT_TRUE(flag);
}


TEST (RummyTest, gameEnd) {
  std::vector<Card> temp;
  Rummy r;
  EXPECT_TRUE(r.gameEnd(temp));
  temp.push_back({"Spades", "5", 5, 0});
  EXPECT_FALSE(r.gameEnd(temp));
}


TEST (RummyTest, changePlayer) {
  std::queue<Player*> players;
  std::queue<std::vector<Card>> playersHands;
  std::vector<Card> playersHand;
  Player * currentPlayer;
  Rummy r;
  playersHand.push_back({"Spades", "5", 5, 0});

  players.push(new Player("1"));
  players.push(new Player("2"));
  playersHands.push(playersHand);
  playersHand.push_back({"Spades", "5", 5, 0});
  playersHands.push(playersHand);
  std::vector<Card> temp = playersHands.front();
  EXPECT_EQ(temp.size(), 1);
  currentPlayer = players.front();
  EXPECT_TRUE(currentPlayer->getName() == "1");
  EXPECT_TRUE(temp.size() == 1);
  r.changePlayer(players, playersHands, playersHand, currentPlayer);
  EXPECT_TRUE(currentPlayer->getName() == "2");
}

TEST (RummyTest, moveFromStockToDiscard) {
  Rummy r;
  std::vector<Card> stock;
  stock.push_back({"Spades", "5", 5, 0});
  std::vector<Card> discard;
  r.moveFromStocktoDiscard(stock, discard);
    EXPECT_TRUE(0 == stock.size());
    EXPECT_TRUE(1 == discard.size());

}