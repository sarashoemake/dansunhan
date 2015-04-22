/*
 * value.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "value.h"

#include <cassert>
#include <cmath>

using namespace std;

bool Value::isValid(int value) {
  int absvalue = abs(value);

  return absvalue <= CHECKMATE || absvalue == INFINITE;
}

bool Value::isCheckmate(int value) {
  assert(isValid(value));

  int absvalue = abs(value);

  return absvalue >= CHECKMATE_THRESHOLD && absvalue <= CHECKMATE;
}



