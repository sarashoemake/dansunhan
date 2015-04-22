/*
 * piece_type.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "piece_type.h"
#include "color.h"

#include <cassert>

using namespace std;

const array<int, PieceType::VALUES_SIZE> PieceType::values = {
  PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

bool PieceType::isValid(int piecetype) {
  switch (piecetype) {
    case PAWN:
    case KNIGHT:
    case BISHOP:
    case ROOK:
    case QUEEN:
    case KING:
      return true;
    default:
      return false;
  }
}

bool PieceType::isValidPromotion(int piecetype) {
  switch (piecetype) {
    case KNIGHT:
    case BISHOP:
    case ROOK:
    case QUEEN:
      return true;
    default:
      return false;
  }
}

bool PieceType::isSliding(int piecetype) {
  switch (piecetype) {
    case BISHOP:
    case ROOK:
    case QUEEN:
      return true;
    case PAWN:
    case KNIGHT:
    case KING:
      return false;
    default:
      throw exception();
  }
}

int PieceType::getValue(int piecetype) {
  switch (piecetype) {
    case PAWN:
      return PAWN_VALUE;
    case KNIGHT:
      return KNIGHT_VALUE;
    case BISHOP:
      return BISHOP_VALUE;
    case ROOK:
      return ROOK_VALUE;
    case QUEEN:
      return QUEEN_VALUE;
    case KING:
      return KING_VALUE;
    default:
      throw exception();
  }
}


