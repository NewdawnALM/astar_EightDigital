#include "game.h"
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

CGame::CGame(const CChess &_start, const CChess &_end): m_startChess(_start),
	m_endChess(_end), bCanSolve(false), iSteps(0), vecSolve{},
	iMaxStates(0), lRunTime(0)
{
	// if(m_startChess.iRow != m_endChess.iRow) {
	// 	throw CException(2001, "开始字符串和结束字符串的行不相同！");
	// }
	// if(m_startChess.iCol != m_endChess.iCol) {
	// 	throw CException(2002, "开始字符串和结束字符串的列不相同！");
	// }
	auto tmp_start = m_startChess.getStrState();
	auto tmp_end = m_endChess.getStrState();
	sort(tmp_start.begin(), tmp_start.end());
	sort(tmp_end.begin(), tmp_end.end());
	if(tmp_start != tmp_end) {
		throw CException(2003, "开始字符串和结束字符串含有的字符有差别！");
	}
}

set<CChess> CGame::getStateByStartAndSteps(const CChess &start, int steps)
{
	set<CChess> retSet;
	set<CChess> inSet;
	inSet.insert(start);
	queue<CChess> queChess;
	queChess.push(start);
	while(!queChess.empty()) {
		CChess curChess = queChess.front();
		queChess.pop();
		if(curChess.iSteps > steps) {
			continue;
		}
		if(curChess.iSteps == steps) {
			retSet.insert(curChess);
			continue;
		}
		auto nextChess = curChess.getNextState();
		int len = nextChess.size();
		for(int i = 0; i < len; ++i) {
			if(inSet.find(nextChess[i]) == inSet.end()) {
				queChess.push(nextChess[i]);
				inSet.insert(nextChess[i]);
			}
		}
	}
	return retSet;
}

struct priority_chess
{
	bool operator () (const CChess &lhs, const CChess &rhs) const
	{
		return lhs.astar_h() > rhs.astar_h();
	}
};

void CGame::run()
{
	CTimeVal _time;

	set<CChess> setChess;
	setChess.insert(m_startChess);
	priority_queue<CChess, vector<CChess>, priority_chess> queChess;
	queChess.push(m_startChess);

	while(!queChess.empty()) {
		// 此处一定要用引用指向set中暂存的变量！不能是局部 变量，因为它的后继结点需要指向一个不会销毁的值！
		const CChess &nowChess = *setChess.find(queChess.top());
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
		vector<CChess> nextChess = nowChess.getNextState();
		int len = nextChess.size();
		for(int i = 0; i < len; ++i) {
			auto chess_it = setChess.find(nextChess[i]);
			if(chess_it == setChess.end()) {
				queChess.push(nextChess[i]);
				setChess.insert(nextChess[i]);
			} else {
				if(chess_it->astar_f() > nextChess[i].astar_f()) {
					setChess.erase(chess_it);
					setChess.insert(nextChess[i]);
					queChess.push(nextChess[i]);
				}
			}
		}
		iMaxStates = max(iMaxStates, int(setChess.size()));
		if(iMaxStates > 300 * 10000) {
			break ;
		}
	}
	lRunTime = _time.costTime();
}

