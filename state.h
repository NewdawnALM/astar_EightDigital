#ifndef  __state_h
#define  __state_h

#include <cstddef>
#include <vector>
using std::vector;

class CState
{
public:
	CState();
	virtual bool operator < (const CState &) const=0;
	virtual void checkSomeFields(const CState &) const;
	virtual vector<CState*> getNextState() const=0;
	virtual size_t astar_f() const=0;
	virtual size_t astar_g() const=0;
	virtual size_t astar_h() const=0;
	virtual ~CState();

	int iSteps;
	const CState *pparent;		// 必须指向实实际际存在的值！注意不要指向一个局部变量等！
};

#endif
