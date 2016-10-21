#ifndef  __CCHESS_H
#define  __CCHESS_H

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ostream;


class CChess
{
    friend ostream& operator << (ostream &, const CChess &);
    static int iLimitNum;
public:
    CChess(const string &state, int row, int col, const string &standard="");

    bool operator < (const CChess &rhs) const;
    bool operator == (const CChess &rhs) const;

    const string& getStrState() const;
    void setStrStandard(const string &);
    vector<CChess> getNextState() const;

    int astar_f() const;
    int astar_g() const;
    int astar_h() const;

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
    int iSteps;
    const CChess *pparent;      // 必须指向实实际际存在的值！注意不要指向一个局部变量等！
    int iMoveFromLast;

    static const string directs[5];
    enum DIRECT
    {
        UP, DOWN, LEFT, RIGHT, UNKOWN
    };

    void output(ostream &out, const string &colSpace=" ", const string &rowSpace="\n") const;
};

#endif
