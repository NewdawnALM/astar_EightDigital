#ifndef  __CCHESS_H
#define  __CCHESS_H

#include "state.h"
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ostream;


class CChess: public CState
{
    friend ostream& operator << (ostream &, const CChess &);
    static int iLimitNum;
public:
    CChess(const string &state, int row, int col, const string &standard="");

    virtual bool operator < (const CState &) const;
    virtual void checkSomeFields(const CState &) const;

    const string& getStrState() const;
    void setStrStandard(const string &);
    virtual vector<CState*> getNextState() const;

    virtual size_t astar_f() const;
    virtual size_t astar_g() const;
    virtual size_t astar_h() const;

private:
    void check_row_col() const;
    void check_value() const;
    void check_standard() const;
    inline int countNotMatch() const;
    inline int countLocalNotMatch(int, int) const;

private:
    string strState;
    int iRow, iCol;
    int iZeroIdx;
    string strStandard;
    int iNotMatch;

public:
    int iMoveFromLast;
    static const string directs[5];
    enum DIRECT
    {
        UP, DOWN, LEFT, RIGHT, UNKOWN
    };
    void output(ostream &out, const string &colSpace=" ", const string &rowSpace="\n") const;
};

#endif
