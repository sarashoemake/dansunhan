/*
 * dansunhan.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "dansunhan.h"
#include "castling_type.h"
#include "file.h"
#include "rank.h"

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

void Dansunhan::run() {
	cin.exceptions(iostream::eofbit|iostream::failbit|iostream::badbit);
	while (true) {
		string line;
		getline(cin, line);
		istringstream input(line);

		string token;
		input >> skipws >> token;
		if (token == "uci") {
			receiveInitialize();
		} else if (token == "isready") {
			receiveReady();
		} else if (token =="ucinewgame") {
			receiveNewGame();
		} else if (token =="position") {
			receivePosition(input);
		} else if (token =="go") {
			receiveGo(input);
		} else if (token =="stop") {
			receiveStop();
		} else if (token =="ponderhit") {
			receivePonderHit();
		} else if (token == "quit") {
				receiveQuit();
				break;
		}
	}
}

void Dansunhan::receiveQuit() {
	//Received quit command. Stop calculating!
	search->quit();
}

void Dansunhan::receiveInitialize() {
	search->stop();

	  // We received an initialization request.

	  // We could do some global initialization here. Probably it would be best
	  // to initialize all tables here as they will exist until the end of the
	  // program.

	  // We must send an initialization answer back!

	cout << "dansunhan" << endl;
	cout << "by Sara Shoemake" << endl;
	cout << "uci ok" << endl;
}

void Dansunhan::receiveReady() {
	  // We received a ready request. We must send the token back as soon as we
	  // can. However, because we launch the search in a separate thread, our main
	  // thread is able to handle the commands asynchronously to the search. If we
	  // don't answer the ready request in time, our engine will probably be
	  // killed by the GUI.
	cout << "ready ok" <<endl;
}

void Dansunhan::receiveNewGame() {
	search->stop();
	  // We received a new game command.
	  // Initialize per-game settings here.
	*currentPosition = Notation::toPosition(Notation::STANDARDPOSITION);
}

void Dansunhan::receivePosition(istringstream& input) {
	search->stop();
	//We received a position command. Just setup position
	  string token;
	  input >> token;
	  if (token == "startpos") {
	    *currentPosition = Notation::toPosition(Notation::STANDARDPOSITION);

	    if (input >> token) {
	      if (token != "moves") {
	        throw exception();
	      }
	    }
	  } else if (token == "fen") {
	    string fen;

	    while (input >> token) {
	      if (token == "moves") {
	        break;
	      } else {
	        fen += token + " ";
	      }
	    }

	    *currentPosition = Notation::toPosition(fen);
	  } else {
	    throw exception();
	  }

	  MoveGenerator moveGenerator;

	  while (input >> token) {
	    // Verify moves
	    MoveList<MoveEntry>& moves = moveGenerator.getLegalMoves(*currentPosition, 1, currentPosition->isCheck());
	    bool found = false;
	    for (int i = 0; i < moves.size; ++i) {
	      int move = moves.entries[i]->move;
	      if (fromMove(move) == token) {
	        currentPosition->makeMove(move);
	        found = true;
	        break;
	      }
	    }

	    if (!found) {
	      throw exception();
	    }
	  }
}

void Dansunhan::receiveGo(istringstream& input) {
	search->stop();
	// We received a start command. Extract all parameters from the
	  // command and start the search.
	  string token;
	  input >> token;
	  if (token == "depth") {
	    int searchDepth;
	    if (input >> searchDepth) {
	      search->newDepthSearch(*currentPosition, searchDepth);
	    } else {
	      throw exception();
	    }
	  } else if (token == "nodes") {
	    uint64_t searchNodes;
	    if (input >> searchNodes) {
	      search->newNodesSearch(*currentPosition, searchNodes);
	    }
	  } else if (token == "movetime") {
	    uint64_t searchTime;
	    if (input >> searchTime) {
	      search->newTimeSearch(*currentPosition, searchTime);
	    }
	  } else if (token == "infinite") {
	    search->newInfiniteSearch(*currentPosition);
	  } else {
	    uint64_t whiteTimeLeft = 1;
	    uint64_t whiteTimeIncrement = 0;
	    uint64_t blackTimeLeft = 1;
	    uint64_t blackTimeIncrement = 0;
	    int searchMovesToGo = 40;
	    bool ponder = false;

	    do {
	      if (token == "wtime") {
	        if (!(input >> whiteTimeLeft)) {
	          throw exception();
	        }
	      } else if (token == "winc") {
	        if (!(input >> whiteTimeIncrement)) {
	          throw exception();
	        }
	      } else if (token == "btime") {
	        if (!(input >> blackTimeLeft)) {
	          throw exception();
	        }
	      } else if (token == "binc") {
	        if (!(input >> blackTimeIncrement)) {
	          throw exception();
	        }
	      } else if (token == "movestogo") {
	        if (!(input >> searchMovesToGo)) {
	          throw exception();
	        }
	      } else if (token == "ponder") {
	        ponder = true;
	      }
	    } while (input >> token);

	    if (ponder) {
	      search->newPonderSearch(*currentPosition,
	        whiteTimeLeft, whiteTimeIncrement, blackTimeLeft, blackTimeIncrement, searchMovesToGo);
	    } else {
	      search->newClockSearch(*currentPosition,
	        whiteTimeLeft, whiteTimeIncrement, blackTimeLeft, blackTimeIncrement, searchMovesToGo);
	    }
	  }

	  // Go...
	  search->start();
	  startTime = chrono::system_clock::now();
	  statusStartTime = startTime;
}

void Dansunhan::receivePonderHit() {
	search->ponderhit();
}

void Dansunhan::receiveStop() {
	search->stop();
}

void Dansunhan::sendBestMove(int bestMove, int ponderMove) {
	cout << "bestmove ";
	if (bestMove != Move::NOMOVE) {
		cout << fromMove(bestMove);
		if (ponderMove != Move::NOMOVE) {
			cout << " ponder " << fromMove(ponderMove);
		}
	} else {
		cout << "nomove";
	}
	cout << endl;
}

void Dansunhan::sendStatus(
    int currentDepth, int currentMaxDepth, uint64_t totalNodes, int currentMove, int currentMoveNumber) {
  if (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - statusStartTime).count() >= 1000) {
    sendStatus(false, currentDepth, currentMaxDepth, totalNodes, currentMove, currentMoveNumber);
  }
}

void Dansunhan::sendStatus( bool force, int currentDepth, int currentMaxDepth, uint64_t totalNodes, int currentMove, int currentMoveNumber) {
	auto timeDelta = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - startTime);
	if (force || timeDelta.count() >= 1000) {
		cout << "info";
		cout << " depth " << currentDepth;
		cout << " seldepth " << currentMaxDepth;
		cout << " nodes " << totalNodes;
		cout << " time " << timeDelta.count();
		cout << " nps " << (timeDelta.count() >= 1000 ? (totalNodes*1000)/timeDelta.count() : 0);

		if (currentMove != Move::NOMOVE) {
			cout << " currmove " << fromMove(currentMove);
			cout << " currmovenumber " << currentMoveNumber;
		}
		cout << endl;
		statusStartTime = chrono::system_clock::now();
	}
}

void Dansunhan::sendMove(RootEntry entry, int currentDepth, int currentMaxDepth, uint64_t totalNodes) {
  auto timeDelta = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - startTime);

  cout << "info";
  cout << " depth " << currentDepth;
  cout << " seldepth " << currentMaxDepth;
  cout << " nodes " << totalNodes;
  cout << " time " << timeDelta.count();
  cout << " nps " << (timeDelta.count() >= 1000 ? (totalNodes * 1000) / timeDelta.count() : 0);

  if (abs(entry.value) >= Value::CHECKMATE_THRESHOLD) {
    // Calculate mate distance
    int mateDepth = Value::CHECKMATE - abs(entry.value);
    cout << " score mate " << ((entry.value > 0) - (entry.value < 0)) * (mateDepth + 1) / 2;
  } else {
    cout << " score cp " << entry.value;
  }

  if (entry.pv.size > 0) {
    cout << " pv";
    for (int i = 0; i < entry.pv.size; ++i) {
      cout << " " << fromMove(entry.pv.moves[i]);
    }
  }

  cout << endl;

  statusStartTime = chrono::system_clock::now();
}

string Dansunhan::fromMove(int move) {
  string notation;

  notation += Notation::fromSquare(Move::getOriginSquare(move));
  notation += Notation::fromSquare(Move::getTargetSquare(move));

  int promotion = Move::getPromotion(move);
  if (promotion != PieceType::NOPIECETYPE) {
    notation += tolower(Notation::fromPieceType(promotion));
  }

  return notation;
}

