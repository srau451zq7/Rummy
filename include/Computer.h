#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

class Computer : public Player {
 public:
  Computer() {}
  Computer(std::string s) : name(s) {}
  
  virtual int whatDiscard(std::vector<Card>& playersHand);

  virtual std::unordered_map<std::string, std::vector<int>> getAction(
      std::vector<Card>& playersHand, std::vector<std::vector<Card>>& melds,
      std::unordered_map<std::string, std::vector<Card>>& runs);

  
  virtual int pickupDiscard(std::vector<Card>& stock,
                            std::vector<Card>& discard,
                            std::vector<Card>& hand);


  std::vector<int> indexOfASuit(std::vector<Card>& playersHand, int whatSuit);

  virtual void turnHasBegun();

 protected:
  std::string name;
};


#endif
