#include "game.h"
#include "exception.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

void usage(const string &exe_name)
{
	string echo = "Usage: " + exe_name + " start(string) row(positive int) col(positive int) steps(positive int).";
	cout << echo << "\n";
}

template <typename T>
T strTo(const string &str)
{
	stringstream ss;
	ss << str;
	T ret;
	ss >> ret;
	return ret;
}

int main(int argc, char const *argv[])
{
	if(argc < 5) {
		usage(argv[0]);
		exit(1);
	}
	int row = strTo<int>(argv[2]);
	int col = strTo<int>(argv[3]);
	if(!row || !col) {
		usage(argv[0]);
		exit(2);
	}
	int steps = strTo<int>(argv[4]);
	string strStandard(argv[1]);
	bool outputOne = true;
	if(argc >= 6) {
		outputOne = false;
	}
	try {
		CChess start(strStandard, row, col);
		auto setChess = CGame::getStateByStartAndSteps(start, steps);
		if(setChess.size() == 0) {
			throw CException(3001, "走不了这么多步！");
		}
		if(outputOne == true) {
			auto first = *setChess.begin();
			first.output(cout);
			cout << "\t\t" << first.getStrState() << "\n";
		}
		else {
			cout << "setChess.size() = " << setChess.size() << "\n";
			for_each(setChess.begin(), setChess.end(), [](const CChess &ch) {
				ch.output(cout);
				cout << "\t\t" << ch.getStrState() << "\n";
			});
		}

	} catch(const CException &ex) {
		cerr << ex.code << ": " << ex.msg << "\n";
		exit(3);
	} catch(...) {
		cerr << "unkown error.\n";
		exit(4);
	}
	return 0;
}