#ifndef  __GAME_H
#define  __GAME_H

#include "chess.h"

class CGame
{
public:
	CGame(const CChess &_start, const CChess &_end);
	static vector<CChess> getNextChess(const CChess &nowChess);
	static vector<CChess> getStateByStartAndSteps(const CChess &start, int steps);
	void run();

	const CChess m_startChess, m_endChess;
	bool bCanSolve;
	int iSteps;
	vector<CChess> vecSolve;

	long long lRunTime;
	int iMaxStates;
};

#endif
