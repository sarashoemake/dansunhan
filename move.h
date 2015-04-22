/*
 * move.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "square.h"
#include "piece.h"
#include "piece_type.h"
#include "move_type.h"

/*
 * Move is represented by int value:
 * 0 - 2: type
 * 3 - 9: origin square
 * 10 - 16: target square
 * 17 - 21: origin piece
 * 22 - 26: target piece
 * 27 - 29: promotion type
 */
class Move {
private:
  // These are our bit masks
  static const int TYPE_SHIFT = 0;
  static const int TYPE_MASK = MoveType::MASK << TYPE_SHIFT;
  static const int ORIGIN_SQUARE_SHIFT = 3;
  static const int ORIGIN_SQUARE_MASK = Square::MASK << ORIGIN_SQUARE_SHIFT;
  static const int TARGET_SQUARE_SHIFT = 10;
  static const int TARGET_SQUARE_MASK = Square::MASK << TARGET_SQUARE_SHIFT;
  static const int ORIGIN_PIECE_SHIFT = 17;
  static const int ORIGIN_PIECE_MASK = Piece::MASK << ORIGIN_PIECE_SHIFT;
  static const int TARGET_PIECE_SHIFT = 22;
  static const int TARGET_PIECE_MASK = Piece::MASK << TARGET_PIECE_SHIFT;
  static const int PROMOTION_SHIFT = 27;
  static const int PROMOTION_MASK = PieceType::MASK << PROMOTION_SHIFT;

public:
  // We don't use 0 as a null value to protect against errors.
  static const int NOMOVE = (MoveType::NOMOVETYPE << TYPE_SHIFT)
      | (Square::NOSQUARE << ORIGIN_SQUARE_SHIFT)
      | (Square::NOSQUARE << TARGET_SQUARE_SHIFT)
      | (Piece::NOPIECE << ORIGIN_PIECE_SHIFT)
      | (Piece::NOPIECE << TARGET_PIECE_SHIFT)
      | (PieceType::NOPIECETYPE << PROMOTION_SHIFT);

  static int valueOf(int type, int originSquare, int targetSquare, int originPiece, int targetPiece, int promotion);
  static int getType(int move);
  static int getOriginSquare(int move);
  static int getTargetSquare(int move);
  static int getOriginPiece(int move);
  static int getTargetPiece(int move);
  static int getPromotion(int move);

private:
  Move();
  ~Move();
};

#endif /* MOVE_H_ */
