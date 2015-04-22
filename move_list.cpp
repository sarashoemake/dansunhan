/*
 * move_list.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "move_list.h"

#include <cassert>

using namespace std;

template<class T>
MoveList<T>::MoveList() {
  for (unsigned int i = 0; i < entries.size(); ++i) {
    entries[i] = shared_ptr<T>(new T());
  }
}

/*
 * Sorts the move list using a stable insertion sort.
 */
template<class T>
void MoveList<T>::sort() {
  for (int i = 1; i < size; ++i) {
    shared_ptr<T> entry(entries[i]);

    int j = i;
    while ((j > 0) && (entries[j - 1]->value < entry->value)) {
      entries[j] = entries[j - 1];
      --j;
    }

    entries[j] = entry;
  }
}

/**
 * Rates the moves in the list according to "Most Valuable Victim - Least Valuable Aggressor".
 */
template<class T>
void MoveList<T>::rateFromMVVLVA() {
  for (int i = 0; i < size; ++i) {
    int move = entries[i]->move;
    int value = 0;

    int piecetypeValue = PieceType::getValue(Piece::getType(Move::getOriginPiece(move)));
    value += PieceType::KING_VALUE / piecetypeValue;

    int target = Move::getTargetPiece(move);
    if (Piece::isValid(target)) {
      value += 10 * PieceType::getValue(Piece::getType(target));
    }

    assert(value >= (PieceType::KING_VALUE / PieceType::KING_VALUE)
      && value <= (PieceType::KING_VALUE / PieceType::PAWN_VALUE) + 10 * PieceType::QUEEN_VALUE);

    entries[i]->value = value;
  }
}

template class MoveList<MoveEntry>;
template class MoveList<RootEntry>;


