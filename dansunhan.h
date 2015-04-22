/*
 * dansunhan.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#ifndef DANSUNHAN_H_
#define DANSUNHAN_H_

#include "search.h"
#include "notation.h"

using namespace std;

class Dansunhan : public Protocol {
public:
	void run();
	virtual void sendBestMove(int bestMove, int ponderMove);
	virtual void sendStatus(int currentDepth, int currentMaxDepth, uint64_t totalNodes, int currentMove, int currentMoveNumber);
	virtual void sendStatus(bool force, int currentDepth, int currentMaxDepth, uint64_t totalNodes, int currentMove, int currentMoveNumber);
	virtual void sendMove(RootEntry entry, int currentDepth, int currentMaxDepth, uint64_t totalNodes);
	static string fromMove(int move);
private:
	unique_ptr<Search> search = unique_ptr<Search>(new Search(*this));
	chrono::system_clock::time_point startTime;
	chrono::system_clock::time_point statusStartTime;
	unique_ptr<Position> currentPosition = unique_ptr<Position>(new Position(Notation::toPosition(Notation::STANDARDPOSITION)));
	void receiveInitialize();
	void receiveReady();
	void receiveNewGame();
	void receivePosition(istringstream& input);
	void receiveGo(istringstream& input);
	void receivePonderHit();
	void receiveStop();
	void receiveQuit();
};


#endif /* DANSUNHAN_H_ */
