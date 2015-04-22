/*
 * bitboard.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <array>
#include <cstdint>

/*
 * Stores squares as bits in a 64-bit long: can
 * convert bit squares to 0x88 squares and 0x88
 * squares to bit squares.
 */

class Bitboard {
public:
  uint64_t squares = 0;

  bool operator==(const Bitboard& bitboard) const;
  bool operator!=(const Bitboard& bitboard) const;

  static int numberOfTrailingZeros(uint64_t b);
  static int bitCount(uint64_t b);
  static int next(uint64_t squares);
  static uint64_t remainder(uint64_t);
  int size();
  void add(int square);
  void remove(int square);

private:
  static const uint64_t DEBRUIJN64 = 0x03F79D71B4CB0A89ULL;
  static const std::array<int, 64> lsbTable;

  static int toX88Square(int square);
  static int toBitSquare(int square);
};

#endif /* BITBOARD_H_ */
