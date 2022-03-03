#include "Computer.h"

#include <algorithm>

int Computer::whatDiscard(std::vector<Card>& playersHand) { return 0; }

std::unordered_map<std::string, std::vector<int>> Computer::getAction(
    std::vector<Card>& playersHand, std::vector<std::vector<Card>>& melds,
    std::unordered_map<std::string, std::vector<Card>>& runs) {
  std::unordered_map<std::string, std::vector<int>> actions;
  std::vector<int> action;
  actions.insert({{"Melds"}, {action}});
  actions.insert({{"Runs"}, {action}});
  actions.insert({{"LayOffs"}, {action}});

  std::sort(playersHand.begin(), playersHand.end());

  for (int i = 0; i < playersHand.size() - 3; i++) {
    if (playersHand[i].value_ == playersHand[i + 1].value_ &&
        playersHand[i + 1].value_ == playersHand[i + 2].value_) {
      std::vector<int> temp{i, i + 1, i + 2};
      auto x = actions.find("Melds");
      x->second = temp;
      return actions;
    }
  }

  Card c("Six", "Diamonds", 6, 3);
  playersHand.push_back(c);
  std::sort(playersHand.begin(), playersHand.end());

  // spades
  auto x = actions.find("Runs");
  action = indexOfASuit(playersHand, 0);
  x->second = action;

  // hearts
  x = actions.find("Runs");
  action = indexOfASuit(playersHand, 1);
  x->second = action;

  // clubs
  x = actions.find("Runs");
  action = indexOfASuit(playersHand, 2);
  x->second = action;

  // diamonds
  x = actions.find("Runs");
  action = indexOfASuit(playersHand, 3);
  x->second = action;

  return actions;
}

int Computer::pickupDiscard(std::vector<Card>& stock,
                            std::vector<Card>& discard,
                            std::vector<Card>& hand) {
  return 1;
}

std::vector<int> Computer::indexOfASuit(std::vector<Card>& playersHand,
                                        int whatSuit) {
  std::vector<int> temp;
  std::vector<int> x;
  for (int i = 0; i < playersHand.size(); i++)
    if (playersHand[i].suit_ == whatSuit) temp.push_back(i);

  if (3 <= temp.size()) {
    for (int i = 0; i < temp.size() - 3; i++) {
      if (playersHand[temp[i]].value_ + 1 == playersHand[temp[i + 1]].value_ &&
          playersHand[temp[i + 1]].value_ + 1 ==
              playersHand[temp[i + 2]].value_) {
        std::vector<int> y{temp[i], temp[i + 1], temp[i + 2]};
        return y;
      }
    }
  }
  return x;
}

void Computer::turnHasBegun() {
  std::cout << this->name << " turn has begun: " << std::endl;
}
