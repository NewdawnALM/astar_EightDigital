#include "state.h"
#include <algorithm>
using std::for_each;

CState::CState(): iSteps(0), pparent(NULL) {}

void CState::checkSomeFields(const CState &) const {}

vector<CState*> CState::__getNextState() const
{
	vector<CState*> nextState = getNextState();
	for_each(nextState.begin(), nextState.end(), [this](CState *pstate) {
		pstate->iSteps = this->iSteps + 1;
		pstate->pparent = this;
	});
	return nextState;
}

size_t CState::astar_f() const
{
	return iSteps;
}

size_t CState::astar_h() const
{
	return astar_f() + astar_g();
}

CState::~CState() {}
