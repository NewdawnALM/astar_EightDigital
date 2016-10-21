#ifndef  __GAME_H
#define  __GAME_H

#include "chess.h"
#include <set>
using std::set;

class CGame
{
public:
	CGame(const CChess &_start, const CChess &_end);
	static set<CChess> getStateByStartAndSteps(const CChess &start, int steps);
	void run();

	const CChess m_startChess, m_endChess;
	bool bCanSolve;
	int iSteps;
	vector<CChess> vecSolve;

	long long lRunTime;
	int iMaxStates;
};

#endif
