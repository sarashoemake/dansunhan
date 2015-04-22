/*
 * move_list.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef MOVE_LIST_H_
#define MOVE_LIST_H_

#include "value.h"
#include "move.h"

#include <array>
#include <memory>

using namespace std;


/**
 * This class stores our moves for a specific position. For the root node we
 * will populate pv for every root move.
 */
template<class T>
class MoveList {
private:
  static const int MAX_MOVES = 256;

public:
  array<shared_ptr<T>, MAX_MOVES> entries;
  int size = 0;

  MoveList();

  void sort();
  void rateFromMVVLVA();
};

class MoveVariation {
public:
  array<int, Depth::MAX_PLY> moves;
  int size = 0;
};

class MoveEntry {
public:
  int move = Move::NOMOVE;
  int value = Value::NOVALUE;
};

class RootEntry : public MoveEntry {
public:
  MoveVariation pv;
};



#endif /* MOVE_LIST_H_ */
