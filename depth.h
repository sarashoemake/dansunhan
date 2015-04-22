/*
 * depth.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef DEPTH_H_
#define DEPTH_H_

class Depth {
public:
  static const int MAX_PLY = 256;
  static const int MAX_DEPTH = 64;

private:
  Depth();
  ~Depth();
};

#endif /* DEPTH_H_ */
