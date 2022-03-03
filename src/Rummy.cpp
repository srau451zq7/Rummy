#include "Rummy.h"

#include <algorithm>
#include <fstream>

#include "Rummy.h"

int Rummy::getDeck(std::vector<Card>& deck) {
  std::fstream input;
  input.open("cards.dat");
  if (input.is_open()) {
    Card c;

    input >> c.value;
    input >> c.suit;
    input >> c.value_;
    input >> c.suit_;

    deck.push_back(c);

    while (input.eof() != true) {
      input >> c.value;
      input >> c.suit;
      input >> c.value_;
      input >> c.suit_;
      deck.push_back(c);
    }
  }
  input.close();

  return deck.size();
}

void Rummy::shuffle(std::vector<Card>& deck) {
  std::random_shuffle(deck.begin(), deck.end());
}

void Rummy::addPlayers(std::queue<Player*>& players, int& playerCount) {
  Player* ptr;
  ptr = new Player("Your");
  players.push(ptr);
  char c;
  for (int i = 0; i < playerCount - 1; i++) {
    char c = static_cast<char>(i + 49);
    std::string temp = "Computer ";
    temp.push_back(c);
    ptr = new Computer(temp);
    players.push(ptr);
  }
}

void Rummy::deal(std::queue<std::vector<Card>>& playersHands,
                 std::vector<Card>& deck, int& playerCount) {
  std::vector<Card> temp;
  int cardsPerPlayer;
  if (playerCount <= 2) {
    cardsPerPlayer = 10;
  } else if (playerCount <= 4) {
    cardsPerPlayer = 7;
  } else {
    cardsPerPlayer = 6;
  }

  for (int i = 0; i < playerCount; i++) {
    for (int j = 0; j < cardsPerPlayer; j++) {
      temp.push_back(deck.back());
      deck.pop_back();
    }
    playersHands.push(temp);
    temp.clear();
  }
}

void Rummy::sort(std::vector<Card> & playersHand) {
    std::sort(playersHand.begin(), playersHand.end());
}

void Rummy::fillBoard(
    std::vector<std::vector<Card>>& melds,
    std::unordered_map<std::string, std::vector<Card>>& runs) {
  Card c("x", "x", 0, 0);
  std::vector<Card> temp;

  for (int i = 0; i < MAX; i++) {
    temp.push_back(c);
  }

  runs.insert({{"Spades"}, {temp}});
  runs.insert({{"Hearts"}, {temp}});
  runs.insert({{"Clubs"}, {temp}});
  runs.insert({{"Diamonds"}, {temp}});
}

bool Rummy::gameEnd(std::vector<Card>& hand) {
  if (hand.size() <= 0) {
    return true;
  } else {
    return false;
  }
}

void Rummy::changePlayer(std::queue<Player*>& players,
                         std::queue<std::vector<Card>>& playersHands,
                         std::vector<Card>& playersHand,
                         Player *& currentPlayer) {
  
  playersHands.pop();
  playersHands.push(playersHand);
  playersHand = playersHands.front();

  players.pop();
  players.push(currentPlayer);
  currentPlayer = players.front();
}

void Rummy::moveFromStocktoDiscard(std::vector<Card>& stock,
                                   std::vector<Card>& discardPile) {
  discardPile.push_back(stock.back());
  stock.pop_back();
}

void Rummy::playHand(std::unordered_map<std::string, std::vector<int>>& actions,
                     std::vector<Card>& playersHand,
                     std::unordered_map<std::string, std::vector<Card>>& runs,
                     std::vector<std::vector<Card>>& melds) {
  // melds
  std::cout << "hello";
  auto x = actions.find("Melds");
  std::sort(x->second.begin(), x->second.end());
  if (x->second.size() == 3) {
    if (playersHand[x->second[0]].value == playersHand[x->second[1]].value &&
        playersHand[x->second[1]].value == playersHand[x->second[2]].value) {
      std::vector<Card> meld;
      meld.push_back(playersHand[x->second[0]]);
      meld.push_back(playersHand[x->second[1]]);
      meld.push_back(playersHand[x->second[2]]);
      melds.push_back(meld);
      playersHand.erase(playersHand.begin() + x->second[0],
                        playersHand.begin() + x->second[0] + 3);
    }
  }

  // runs
  x = actions.find("Runs");
  std::sort(x->second.begin(), x->second.end());
  if (x->second.size() == 3) {
    bool flag = true;
    int value = playersHand[x->second[0]].value_;
    int suit = playersHand[x->second[0]].suit_;

    if (value == playersHand[x->second[0]].value_ &&
        value + 1 == playersHand[x->second[1]].value_ &&
        value + 2 == playersHand[x->second[2]].value_ &&
        suit == playersHand[x->second[0]].suit_ &&
        suit == playersHand[x->second[1]].suit_ &&
        suit == playersHand[x->second[2]].suit_) {
      auto runs_ = runs.find(playersHand[x->second[0]].suit);
      runs_->second[playersHand[x->second[0]].value_ - 1] =
          playersHand[x->second[0]];
      runs_->second[playersHand[x->second[1]].value_ - 1] =
          playersHand[x->second[1]];
      runs_->second[playersHand[x->second[2]].value_ - 1] =
          playersHand[x->second[2]];

      playersHand.erase(playersHand.begin() + x->second[0]);
      playersHand.erase(playersHand.begin() + x->second[1] - 1);
      playersHand.erase(playersHand.begin() + x->second[2] - 2);
    }
  }

  // layoffs
  x = actions.find("LayOffs");
  std::sort(x->second.begin(), x->second.end());
  if (x->second.size() > 0) {
    for (int i = 0; i < x->second.size(); i++) {
      auto runs_ = runs.find(playersHand[x->second[i]].suit);
      runs_->second[playersHand[x->second[i]].value_ - 1] =
          playersHand[x->second[i]];  // this
      playersHand.erase(playersHand.begin() + x->second[i] - i);
    }
  }
}

void Rummy::discard(std::vector<Card>& playersHand,
                    std::vector<Card>& discardPile, int whatCard) {
  Card c = playersHand[whatCard];
  playersHand.erase(playersHand.begin() + whatCard);
  discardPile.push_back(c);
}
