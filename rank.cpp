/*
 * rank.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "rank.h"

using namespace std;

const array<int, Rank::VALUES_SIZE> Rank::values = {
  r1, r2, r3, r4, r5, r6, r7, r8
};

bool Rank::isValid(int rank) {
  switch (rank) {
    case r1:
    case r2:
    case r3:
    case r4:
    case r5:
    case r6:
    case r7:
    case r8:
      return true;
    default:
      return false;
  }
}


