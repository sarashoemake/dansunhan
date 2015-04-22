/*
 * main.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sarashoemake
 */

#include "dansunhan.h"
#include "perft.h"

#include <string>
#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
	try {
		if (argc==2) {
			string token(argv[1]);
			if (token == "perft") {
				unique_ptr<Perft> perft(new Perft());
				perft -> run();
			}
		} else {
			unique_ptr<Dansunhan> dansunhan(new Dansunhan());
			dansunhan->run();
		}
	} catch (exception& e) {
		cout << "Exiting dansunhan due to an exception: " << e.what() << endl;
		return 1;
	}
}


