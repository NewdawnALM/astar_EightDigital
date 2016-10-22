#ifndef  __ASTAR_H
#define  __ASTAR_H

#include "state.h"
#include <set>
using std::set;

class CAstar
{
public:
	CAstar(const CState &_start, const CState &_end);
	static set<const CState*> getStateByStartAndSteps(const CState &start, int steps);
	void run();
	~CAstar();

	const CState &m_rStart, &m_rEnd;
	bool bCanSolve;
	int iSteps;
	vector<const CState*> vecSolve;
	long lRunTime;
	int iTotalStates;
};

#endif
