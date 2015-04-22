/*
 * perft.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef PERFT_H_
#define PERFT_H_

#include "move_generator.h"

using namespace std;

class Perft {
public:
  void run();

private:
  static const int MAX_DEPTH = 6;

  array<MoveGenerator, MAX_DEPTH> moveGenerators;

  uint64_t miniMax(int depth, Position& position, int ply);
};


#endif /* PERFT_H_ */
