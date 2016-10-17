#include "game.h"
#include <set>
#include <queue>
#include <algorithm>
using std::set;
using std::queue;
using std::swap;
using std::max;
#include "timeval.h"

CGame::CGame(const CChess &_start, const CChess &_end): m_startChess(_start),
	m_endChess(_end), bCanSolve(false), iSteps(0), vecSolve{},
	iMaxStates(0), lRunTime(0) { }

vector<CChess> CGame::getNextChess(const CChess &nowChess)
{
	vector<CChess> nextChess;
	const int zeroIdx = nowChess.iZeroIdx;
	// 0可以和上面的数字进行交换
	if(zeroIdx >= nowChess.iCol) {
		CChess up(nowChess);
		swap(up.strState[zeroIdx - up.iCol], up.strState[zeroIdx]);
		up.iZeroIdx -= up.iCol;
		++up.iSteps;
		up.pparent = const_cast<CChess*>(&nowChess);
		up.iMoveFromLast = DOWN;
		nextChess.push_back(up);
	}
	if(zeroIdx < nowChess.strState.size() - nowChess.iCol) {
		CChess down(nowChess);
		swap(down.strState[zeroIdx + down.iCol], down.strState[zeroIdx]);
		down.iZeroIdx += down.iCol;
		++down.iSteps;
		down.pparent = const_cast<CChess*>(&nowChess);
		down.iMoveFromLast = UP;
		nextChess.push_back(down);
	}
	if(zeroIdx % nowChess.iCol != 0) {
		CChess left(nowChess);
		swap(left.strState[zeroIdx - 1], left.strState[zeroIdx]);
		--left.iZeroIdx;
		++left.iSteps;
		left.pparent = const_cast<CChess*>(&nowChess);
		left.iMoveFromLast = RIGHT;
		nextChess.push_back(left);
	}
	if((zeroIdx + 1) % nowChess.iCol != 0) {
		CChess right(nowChess);
		swap(right.strState[zeroIdx + 1], right.strState[zeroIdx]);
		++right.iZeroIdx;
		++right.iSteps;
		right.pparent = const_cast<CChess*>(&nowChess);
		right.iMoveFromLast = LEFT;
		nextChess.push_back(right);
	}
	return nextChess;
}

void CGame::run()
{
	CTimeVal _time;

	set<CChess> setChess;
	setChess.insert(m_startChess);
	queue<CChess> queChess;
	queChess.push(m_startChess);

	while(!queChess.empty()) {
		// 此处一定要用引用指向set中暂存的变量！不能是局部 变量，因为它的后继结点需要指向一个不会销毁的值！
		const CChess &nowChess = *setChess.find(queChess.front());
		queChess.pop();
		if(nowChess == m_endChess) {
			bCanSolve = true;
			iSteps = nowChess.iSteps;
			vecSolve.push_back(nowChess);
			const CChess *lastChess = nowChess.pparent;
			while(lastChess != NULL) {
				vecSolve.push_back(*lastChess);
				lastChess = lastChess->pparent;
			}
			break;
		}
		vector<CChess> nextChess = CGame::getNextChess(nowChess);
		int len = nextChess.size();
		for(int i = 0; i < len; ++i) {
			if(setChess.find(nextChess[i]) == setChess.end()) {
				queChess.push(nextChess[i]);
				setChess.insert(nextChess[i]);
			}
		}
		iMaxStates = max(iMaxStates, int(setChess.size()));
		if(iMaxStates > 300 * 10000) {
			break ;
		}
	}

	lRunTime = _time.costTime();
}