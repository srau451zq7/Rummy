#pragma once
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Computer.h"
#include "Player.h"
#include "Rummy.h"

class Model {
  Rummy& controller;
  Player* currentPlayer;

 public:
  Model(Rummy& _controller, Player* _currentPlayer)
      : controller(_controller), currentPlayer(_currentPlayer) {}

  bool setupGame();

  void runGame();

  ~Model();

  std::queue<Player*> players;
  std::queue<std::vector<Card>> playersHands;
  std::vector<Card> stock;
  std::vector<Card> discardPile;
  std::vector<std::vector<Card>> melds;
  std::unordered_map<std::string, std::vector<Card>> runs;
};


