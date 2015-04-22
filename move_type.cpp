/*
 * move_type.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "move_type.h"

bool MoveType::isValid(int type) {
  switch (type) {
    case NORMAL:
    case PAWNDOUBLE:
    case PAWNPROMOTION:
    case ENPASSANT:
    case CASTLING:
      return true;
    default:
      return false;
  }
}
