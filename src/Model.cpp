#include "Model.h"
#include <algorithm>
#include <fstream>

bool Model::setupGame() {
  controller.getDeck(stock);

  controller.shuffle(stock);

  int numOfPlayers = currentPlayer->startGame();

  controller.addPlayers(players, numOfPlayers);

  controller.deal(playersHands, stock, numOfPlayers);

  controller.fillBoard(melds, runs);

  return true;
}

void Model::runGame() {
  Player* playerPtr;
  std::vector<Card> playersHand;
  int pickOrDiscard;
  int indexNumOfDiscard;
  std::unordered_map<std::string, std::vector<int>> whatPlay;
  playerPtr = players.front();          // gets the currrent player
  playersHand = playersHands.front();  // gets the current players hand

  while (true) {
    controller.sort(playersHand);  // sorts hands of all players

    playerPtr->turnHasBegun();

    if (discardPile.size() == 0 &&
        stock.size() >
            0) {  // checks to make sure the discard pile has at least one card
      controller.moveFromStocktoDiscard(
          stock, discardPile);  // checks to make sure the stock has cards to
                                // move from stock
    }
    pickOrDiscard = playerPtr->pickupDiscard(stock, discardPile, playersHand);
    if (pickOrDiscard == 1) {
      controller.moveFromStocktoDiscard(stock, playersHand);
    } else {
      controller.moveFromStocktoDiscard(discardPile, playersHand);
    }

    whatPlay = playerPtr->getAction(playersHand, melds, runs);

    controller.playHand(whatPlay, playersHand, runs, melds);

    indexNumOfDiscard = playerPtr->whatDiscard(playersHand);

    controller.discard(playersHand, discardPile, indexNumOfDiscard);

    // discard

    if (controller.gameEnd(playersHands.front())) {
      // congrats to player x, end game
      break;
    } else {
      controller.changePlayer(players, playersHands, playersHand, playerPtr);
    }
  }
}

Model::~Model() {
  while (players.size() != 0) {
    Player* ptr = players.front();
    players.pop();
  }
}
