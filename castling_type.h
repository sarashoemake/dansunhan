/*
 * castling_type.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef CASTLING_TYPE_H_
#define CASTLING_TYPE_H_

#include <array>

class CastlingType {
public:
  static const int KINGSIDE = 0;
  static const int QUEENSIDE = 1;

  static const int NOCASTLINGTYPE = 2;

  static const int VALUES_SIZE = 2;
  static const std::array<int, VALUES_SIZE> values;

private:
  CastlingType();
  ~CastlingType();
};

#endif /* CASTLING_TYPE_H_ */
