/*
 * file.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef FILE_H_
#define FILE_H_

#include <array>

class File {
public:
  static const int a = 0;
  static const int b = 1;
  static const int c = 2;
  static const int d = 3;
  static const int e = 4;
  static const int f = 5;
  static const int g = 6;
  static const int h = 7;

  static const int NOFILE = 8;

  static const int VALUES_SIZE = 8;
  static const std::array<int, VALUES_SIZE> values;

  static bool isValid(int file);

private:
  File();
  ~File();
};


#endif /* FILE_H_ */
