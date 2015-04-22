/*
 * move_type.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include <array>
#include <memory>

class MoveType {
public:
  static const int MASK = 0x7;
  static const int NORMAL = 0;
  static const int PAWNDOUBLE = 1;
  static const int PAWNPROMOTION = 2;
  static const int ENPASSANT = 3;
  static const int CASTLING = 4;
  static const int NOMOVETYPE = 5;
  static bool isValid(int type);

private:
  MoveType();
  ~MoveType();
};
