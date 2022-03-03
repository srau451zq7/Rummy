#ifndef RUMMY_H
#define RUMMY_H
#include <queue>
#include <unordered_map>
#include <vector>
#include "Card.h"
#include "Computer.h"
#include "Player.h"

class Rummy {
 public:
  virtual int getDeck(std::vector<Card>& deck);

  virtual void shuffle(std::vector<Card>& deck);

  virtual void addPlayers(std::queue<Player*>& players, int& playerCount);

  virtual void deal(std::queue<std::vector<Card>>& playersHands,
                    std::vector<Card>& deck, int& playerCount);

  virtual void fillBoard(
      std::vector< std::vector<Card>> & melds,
      std::unordered_map<std::string, std::vector<Card>> & runs);

  virtual void sort(std::vector<Card> & playersHand);

  virtual bool gameEnd(std::vector<Card> & hand);

  virtual void changePlayer(std::queue<Player*>& players,
                         std::queue<std::vector<Card>>& playersHands,
                         std::vector<Card>& playersHand,
                         Player *& currentPlayer);
  

  virtual void moveFromStocktoDiscard(std::vector<Card>& stock,
                                      std::vector<Card>& discardPile);


  virtual void playHand(
      std::unordered_map<std::string, std::vector<int>> & actions,
      std::vector<Card>& playersHand,
      std::unordered_map<std::string, std::vector<Card>> & runs,
      std::vector<std::vector<Card>> & melds);

  
  virtual void discard(std::vector<Card>& playersHand,
                       std::vector<Card>& discardPile, int whatCard);

};


#endif    