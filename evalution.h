/*
 * evaluation.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "position.h"

using namespace std;

class Evaluation {
public:
  static const int TEMPO = 1;

  static int materialWeight;
  static int mobilityWeight;

  int evaluate(Position& position);

private:
  static const int MAX_WEIGHT = 100;

  int evaluateMaterial(int color, Position& position);
  int evaluateMobility(int color, Position& position);
  int evaluateMobility(int color, Position& position, int square, const vector<int>& directions);
};



