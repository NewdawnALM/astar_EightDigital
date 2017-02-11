#include "astar.h"
#include "timeval.h"
#include "exception.h"
#include <set>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <functional>
using std::set;
using std::queue;
using std::priority_queue;
using std::swap;
using std::max;
using std::sort;
using std::function;
#define  For(i,s,t)  for(auto i = (s); i != (t); ++i)

CAstar::CAstar(const CState &_start, const CState &_end):
	m_rStart(_start), m_rEnd(_end), bCanSolve(false), iSteps(0), vecSolve{},
	iTotalStates(0), lRunTime(0), pointerWaitToDelete{}
{
	m_rStart.checkSomeFields(m_rEnd);
}

template <typename T>
struct CPointerComp
{
	bool operator () (const T &pl, const T &pr) const
	{
		return *pl < *pr;
	}
};

set<const CState*> CAstar::getStateByStartAndSteps(const CState &start, int steps)
{
	set<const CState*> retSet;
	set<const CState*, CPointerComp<const CState*> > inSet;
	inSet.insert(&start);
	queue<const CState*> queState;
	queState.push(&start);
	while(!queState.empty()) {
		const CState* const pCurState = queState.front();
		queState.pop();
		if(pCurState->iSteps > steps) {
			// continue;
			break;
		}
		if(pCurState->iSteps == steps) {
			retSet.insert(pCurState);
			continue;
		}
		auto nextState = pCurState->__getNextState();
		int len = nextState.size();
		For(i, 0, len) {
			if(inSet.find(nextState[i]) == inSet.end()) {
				queState.push(nextState[i]);
				inSet.insert(nextState[i]);
			} else {
				delete nextState[i];
			}
		}
	}
	inSet.erase(&start);
	For(ret_it, retSet.begin(), retSet.end()) {
		inSet.erase(*ret_it);
	}
	For(ins_it, inSet.begin(), inSet.end()) {
		delete *ins_it;
	}
	return retSet;
}

struct priority_state
{
	bool operator () (const CState* const lhs, const CState* const rhs) const
	{
		return lhs->astar_h() > rhs->astar_h();
	}
};

void CAstar::run()
{
	CTimeVal _time;

	set<const CState*, CPointerComp<const CState*>> setState;
	setState.insert(&m_rStart);
	priority_queue<const CState*, vector<const CState*>, priority_state> queState;
	queState.push(&m_rStart);

	while(!queState.empty()) {
		// auto pHeadState = *(setState.find(queState.top()));
		auto pHeadState = queState.top();
		queState.pop();
		if(!(*pHeadState < m_rEnd) && !(m_rEnd < *pHeadState)) {
			bCanSolve = true;
			iSteps = pHeadState->iSteps;
			vecSolve.push_back(pHeadState);
			const CState *lastState = pHeadState->pparent;
			while(lastState != NULL) {
				vecSolve.push_back(lastState);
				lastState = lastState->pparent;
			}
			break;
		}
		vector<CState*> nextState = pHeadState->__getNextState();
		int len = nextState.size();

		for(int i = 0; i < len; ++i) {
			auto state_it = setState.find(nextState[i]);
			if(state_it == setState.end()) {
				queState.push(nextState[i]);
				setState.insert(nextState[i]);
			} else {
				if((*state_it)->astar_f() > nextState[i]->astar_f()) {
					pointerWaitToDelete.insert(*state_it);		// 这一句要放在setState.erase前面，防止迭代器失效
					setState.erase(state_it);
					setState.insert(nextState[i]);
					queState.push(nextState[i]);
				} else {
					delete nextState[i];
				}
			}
		}
		if(setState.size() > 600 * 10000) {
			break ;
		}
	}
	iTotalStates = setState.size();
	lRunTime = _time.costTime();
	setState.erase(&m_rStart);
	For(vec_it, vecSolve.begin(), vecSolve.end()) {
		setState.erase(*vec_it);
	}
	For(s_it, setState.begin(), setState.end()) {
		delete *s_it;
	}
}

CAstar::~CAstar()
{
	For(vec_it, vecSolve.begin(), vecSolve.end()) {
		if(*vec_it != &m_rStart && *vec_it != &m_rEnd) {
			delete *vec_it;
		}
	}
	for(const auto &pState: pointerWaitToDelete) {
		delete pState;
	}
}
