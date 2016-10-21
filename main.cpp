#include "chess.h"
#include "exception.h"
#include "game.h"
#include "timeval.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	string str;
	int r, c;
	while(true) {
		try {
			cout << "please input the start state(string) and row, col, separate with a space:\n";
			if(bool(cin >> str >> r >> c) == false) {
				break;
			}
			CChess start(str, r, c);
			cout << "please input the end state(string) and row, col, separate with a space:\n";
			if(bool(cin >> str >> r >> c) == false) {
				break;
			}
			CChess end(str, r, c);
			start.setStrStandard(str);

			cout << "Your game is:\n" << start << " --->\n" << end << "\n";

			CGame game(start, end);
			game.run();
			if(game.bCanSolve == true) {
				cout << "your game can be solve:\n";
				cout << "the total steps is: " << game.iSteps << "\n";
				cout << "and the path is:\n";
				int len = game.vecSolve.size();
				cout << game.vecSolve[len - 1] << "\n";
				for(int i = len - 2; i >= 0; --i) {
					cout << "    |\n";
					cout << "    |   " << CChess::directs[game.vecSolve[i].iMoveFromLast] << "\n";
					cout << "   \\|/\n\n";
					cout << game.vecSolve[i] << "\n";
				}
			} else {
				cout << "sorry, your game can't be solve, please input the other state.\n\n";
			}
			cout << " and the max states is: " << game.iMaxStates << "\n";
			cout << " and the runtime is: " << game.lRunTime << "\n";
			
		} catch (const CException &ex) {
			cerr << ex.code << ": " << ex.msg << "\n";
		} catch (...) {
			break;
		}
	}
	return 0;
}
