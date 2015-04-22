/*
 * color.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <array>

class Color {
public:
  static const int WHITE = 0;
  static const int BLACK = 1;

  static const int NOCOLOR = 2;

  static const int VALUES_SIZE = 2;
  static const std::array<int, VALUES_SIZE> values;

  static bool isValid(int color);
  static int opposite(int color);

private:
  Color();
  ~Color();
};



#endif /* COLOR_H_ */
