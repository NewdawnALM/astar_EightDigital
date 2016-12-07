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
	vector<CState*> __getNextState() const;		// call the function getNextState and deal with iSteps and pparent
	virtual long astar_f() const;
	virtual long astar_g() const=0;		// g函数的值越小，优先级就越高，f()和h()函数类似
	virtual long astar_h() const;
	virtual ~CState();

	int iSteps;
	const CState *pparent;		// 必须指向实实际际存在的值！注意不要指向一个局部变量等！
};

#endif
