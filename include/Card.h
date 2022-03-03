#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
 public:
  Card() {}

  Card(std::string _value, std::string _suit, int v, int s)
      : value(_value), suit(_suit), value_(v), suit_(s) {}

  bool operator==(const Card& rhs) {
    if (this->value_ == this->value_ && rhs.suit_ == rhs.suit_) {
      return true;
    } else
      return false;
  }

  bool operator>=(const Card& rhs) {
    if (this->value_ >= rhs.value_) {
      return true;
    } else
      return false;
  }
  bool operator<=(const Card& rhs) {
    if (this->value_ <= rhs.value_) {
      return true;
    } else
      return false;
  }

  bool operator<(const Card& rhs) {
    if (this->value_ < rhs.value_) {
      return true;
    } else
      return false;
  }

  bool operator>(const Card& rhs) {
    if (this->value_ > rhs.value_) {
      return true;
    } else
      return false;
  }


  std::string value;
  std::string suit;
  int value_;
  int suit_;
};

const unsigned int MAX = 13;


#endif