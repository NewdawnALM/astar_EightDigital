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
    CChess(const string &state, int row, int col);
    CChess(const vector<vector<char>> &vec2);
    bool operator < (const CChess &rhs) const;
    bool operator == (const CChess &rhs) const;

    void check_row_col() const ;
    void check_value() const ;
    void output(ostream &out, const string &colSpace=" ", const string &rowSpace="\n") const;

    string strState;
    int iRow, iCol;
    int iSteps;
    int iZeroIdx;
    const CChess *pparent;      // 必须指向实实际际存在的值！注意不要指向一个局部变量等！
    int iMoveFromLast;
    static const string directs[5];

    enum DIRECT
    {
        UP, DOWN, LEFT, RIGHT, UNKOWN
    };
};

#endif
