/*
 * piece_type.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef PIECE_TYPE_H_
#define PIECE_TYPE_H_

#include <array>

class PieceType {
public:
  static const int MASK = 0x7;

  static const int PAWN = 0;
  static const int KNIGHT = 1;
  static const int BISHOP = 2;
  static const int ROOK = 3;
  static const int QUEEN = 4;
  static const int KING = 5;

  static const int NOPIECETYPE = 6;

  static const int VALUES_SIZE = 6;
  static const std::array<int, VALUES_SIZE> values;

  // Piece values as defined by Larry Kaufman
  static const int PAWN_VALUE = 100;
  static const int KNIGHT_VALUE = 325;
  static const int BISHOP_VALUE = 325;
  static const int ROOK_VALUE = 500;
  static const int QUEEN_VALUE = 975;
  static const int KING_VALUE = 20000;

  static bool isValid(int piecetype);
  static bool isValidPromotion(int piecetype);
  static bool isSliding(int piecetype);
  static int getValue(int piecetype);

private:
  PieceType();
  ~PieceType();
};



#endif /* PIECE_TYPE_H_ */
