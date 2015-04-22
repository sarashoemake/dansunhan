/*
 * perft.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "perft.h"
#include "notation.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <memory>

using namespace std;

void Perft::run() {
  unique_ptr<Position> position(new Position(Notation::toPosition(Notation::STANDARDPOSITION)));
  int depth = MAX_DEPTH;

  cout << "Testing " << Notation::fromPosition(*position) << " at depth " << depth << endl;

  auto startTime = chrono::system_clock::now();
  uint64_t result = miniMax(depth, *position, 0);
  auto endTime = chrono::system_clock::now();

  auto duration = endTime - startTime;

  cout << "Nodes: ";
  cout << result << endl;
  cout << "Duration: ";
  cout << setfill('0') << setw(2)
    << chrono::duration_cast<chrono::hours>(duration).count() << ":";
  cout << setfill('0') << setw(2)
    << (chrono::duration_cast<chrono::minutes>(duration)
    - chrono::duration_cast<chrono::minutes>(chrono::duration_cast<chrono::hours>(duration))).count() << ":";
  cout << setfill('0') << setw(2)
    << (chrono::duration_cast<chrono::seconds>(duration)
    - chrono::duration_cast<chrono::seconds>(chrono::duration_cast<chrono::minutes>(duration))).count() << ".";
  cout << setfill('0') << setw(2)
    << (chrono::duration_cast<chrono::milliseconds>(duration)
    - chrono::duration_cast<chrono::milliseconds>(chrono::duration_cast<chrono::seconds>(duration))).count();
  cout << endl;

  cout << "n/ms: "
    << result / chrono::duration_cast<chrono::milliseconds>(duration).count() << endl;
}

uint64_t Perft::miniMax(int depth, Position& position, int ply) {
  if (depth == 0) {
    return 1;
  }

  uint64_t totalNodes = 0;

  bool isCheck = position.isCheck();
  MoveGenerator& moveGenerator = moveGenerators[ply];
  MoveList<MoveEntry>& moves = moveGenerator.getMoves(position, depth, isCheck);
  for (int i = 0; i < moves.size; ++i) {
    int move = moves.entries[i]->move;

    position.makeMove(move);
    if (!position.isCheck(Color::opposite(position.activeColor))) {
      totalNodes += miniMax(depth - 1, position, ply + 1);
    }
    position.undoMove(move);
  }

  return totalNodes;
}


