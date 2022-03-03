#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <unordered_map>
#include "Card.h"

class Player {
 public:
  Player() {}
  Player(std::string s) : name(s) {}
  virtual int startGame();

  virtual int pickupDiscard (std::vector<Card>& stock,
                             std::vector<Card>& discard,
                             std::vector<Card>& hand);


  virtual void printHand(std::vector<Card>& hand);

  virtual std::unordered_map<std::string, std::vector<int>> getAction 
         (std::vector <Card> & playersHand, std::vector<std::vector<Card>>& melds,
      std::unordered_map<std::string, std::vector<Card>> & runs );


  virtual void printMelds(std::vector<std::vector<Card>>& melds);

  virtual void printRuns(
      std::unordered_map<std::string, std::vector<Card>> & runs);

  std::vector<int> getPlay(std::string s, std::vector<Card>& playersHand);

  virtual void turnHasBegun();

  virtual int whatDiscard(std::vector<Card>& playersHand);

  virtual std::string getName();

 protected:
  std::string name;
};
/*
  std::queue<Player*> players;
  std::queue<std::vector<Card>> playersHands;
  std::vector<Card> stock;
  std::vector<Card> discardPile;
  std::unordered_map<std::string, std::vector<Card>> melds;
  std::unordered_map<std::string, std::vector<Card>> runs;
  */

#endif