#include "Player.h"

#include <algorithm>
#include <iostream>

int Player::startGame() {
  int numOfPlayers;
  do {
    std::cout << "Enter the number of players: ";
    std::cin >> numOfPlayers;
  } while (numOfPlayers <= 0 || numOfPlayers >= 7);
  return numOfPlayers;
}

int Player::pickupDiscard(std::vector<Card>& stock, std::vector<Card>& discard,
                          std::vector<Card>& hand) {
  int flag;
  Card c = discard.back();

  printHand(hand);

  std::cout << "The discard shows: " << c.value << " " << c.suit << "\n";
  do {
    std::cout << "Enter 1 to from from stock\n"
              << "Enter 2 to draw from discard\n"
              << ":";
    std::cin >> flag;
  } while (flag < 1 || flag > 2);

  return 2;
}

void Player::printHand(std::vector<Card>& hand) {
  std::cout << "Your hand: \n";
  for (int i = 0; i < hand.size(); i++) {
    std::cout << i + 1 << ". " << hand[i].value << " " << hand[i].suit << "\n";
  }
  std::cout << std::endl;
}

std::unordered_map<std::string, std::vector<int>> Player::getAction(
  std::vector<Card>& playersHand, std::vector<std::vector<Card>>& melds,
  std::unordered_map<std::string, std::vector<Card>>& runs) {
  std::unordered_map<std::string, std::vector<int>> actions;
  std::vector<int> action;

  std::sort(playersHand.begin(), playersHand.end());

  printHand(playersHand);
  printMelds(melds);
  printRuns(runs);

  action = getPlay("Melds", playersHand);
  actions.insert({{"Melds"}, {action}});
  action.clear();

  action = getPlay("Runs", playersHand);
  actions.insert({{"Runs"}, {action}});
  action.clear();

  action = getPlay("LayOffs", playersHand);
  actions.insert({{"LayOffs"}, {action}});
  action.clear();

  return actions;
}

void Player::printMelds(std::vector<std::vector<Card>>& melds) {
  std::cout << "Current Melds: \n";
  for (int i = 0; i < melds.size(); i++) {
    for (int j = 0; j < melds[i].size(); j++) {
      std::cout << melds[i][j].value << " " << melds[i][j].suit << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
}

void Player::printRuns(
    std::unordered_map<std::string, std::vector<Card>>& runs) {
  std::cout << "Current Runs: \n";
  auto run = runs.find("Spades");
  for (int i = 0; i < run->second.size(); i++)
    std::cout << run->second[i].suit << " " << run->second[i].value << " ";
  std::cout << std::endl;

  run = runs.find("Hearts");
  for (int i = 0; i < run->second.size(); i++)
    std::cout << run->second[i].suit << " " << run->second[i].value << " ";
  std::cout << std::endl;

  run = runs.find("Diamonds");
  for (int i = 0; i < run->second.size(); i++)
    std::cout << run->second[i].suit << " " << run->second[i].value << " ";
  std::cout << std::endl;

  run = runs.find("Spades");
  for (int i = 0; i < run->second.size(); i++)
    std::cout << run->second[i].suit << " " << run->second[i].value << " ";
  std::cout << std::endl;
  std::cout << std::endl;
}

std::vector<int> Player::getPlay(std::string s,
                                 std::vector<Card>& playersHand) {
  std::vector<int> action;
  int getAction = 1;
  std::cout << "Enter index number of the cards you win to " << s << std::endl;
  std::cout << "Enter 0 if you wish not to " << s << std::endl;
  while (getAction != 0) {
    std::cin >> getAction;
    if (getAction >= 1 && getAction <= playersHand.size()) {
      action.push_back(getAction - 1);
      std::cout << "You have selected the ";
      std::cout << playersHand[getAction - 1].value << " of ";
      std::cout << playersHand[getAction - 1].suit << "\n";
    } else if (getAction == 0) {
    } else {
      std::cout << "Invalid selection, try again \n";
    }
  }
  return action;
}

int Player::whatDiscard(std::vector<Card>& playersHand) {
  printHand(playersHand);
  int temp;
  do {
    std::cout << "What card would you like to discard?\n";
    std::cin >> temp;
  } while (temp <= 0 || temp >= playersHand.size());
  return temp - 1;
}

void Player::turnHasBegun() {
  std::cout << this->name << " turn has begun: " << std::endl;
}

std::string Player::getName() {
  return name;
}