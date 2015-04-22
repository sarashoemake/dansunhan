/*
 * color.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "color.h"

using namespace std;

const array<int, Color::VALUES_SIZE> Color::values = {
  WHITE, BLACK
};

bool Color::isValid(int color) {
  switch (color) {
    case WHITE:
    case BLACK:
      return true;
    default:
      return false;
  }
}

int Color::opposite(int color) {
  switch (color) {
    case WHITE:
      return BLACK;
    case BLACK:
      return WHITE;
    default:
      throw exception();
  }
}


