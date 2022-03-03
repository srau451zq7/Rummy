#include <algorithm>
#include <iostream>

#include "Card.h"
#include "Model.h"
#include "Player.h"
#include "Rummy.h"
int main() {
  Player* ptr = new Player;
  Rummy r;
  Model m(r, ptr);
  m.setupGame();
  m.runGame();
  return 0;
  delete ptr;
}
