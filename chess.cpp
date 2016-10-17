#include "chess.h"
#include "exception.h"
#include <cstring>
#include <algorithm>
using std::sort;

int CChess::iLimitNum = 20;
const string CChess::directs[5] = {"up", "down", "left", "right", "unkown"};

void CChess::check_row_col() const
{
    if(iRow <= 0 || iCol <= 0) {
        throw CException(1001, "行或列的值不能小于等于0！");
    }
    if(iRow * iCol > iLimitNum) {
        char msg[100];
        sprintf(msg, "行列数的乘积不能超过%d！", iLimitNum);
        throw CException(1002, msg);
    }
    if(iRow * iCol != strState.size()) {
    	throw CException(1003, "行列数的乘积应该和字符串的相等！");
    }
}

void CChess::check_value() const
{
	if(iZeroIdx == string::npos) {
		throw CException(1004, "字符串值不合法，应该含有'0'！");
	}
    bool ch[300];
    memset(ch, 0, sizeof(ch));
    int len = strState.size();
    for(int i = 0; i < len; ++i) {
        if(ch[strState[i]] == true) {
            throw CException(1005, "字符串中不能含有相同的字符！");
        }
        ch[strState[i]] = true;
    }
}

CChess::CChess(const string &state, int row, int col, const string &standard):
    strState(state), iRow(row), iCol(col), iSteps(0), pparent(NULL),
    iMoveFromLast(UNKOWN), strStandard(standard)
{
    this->check_row_col();
	iZeroIdx = strState.find('0');
    this->check_value();

    if(strStandard == "") {
        sort(strStandard.begin(), strStandard.end());
    }
}

CChess::CChess(const vector<vector<char>> &vec2): iRow(vec2.size()), iCol(vec2.size() == 0 ? -1: vec2[0].size())
{
    this->check_row_col();
    for(int i = 0; i < iRow; ++i) {
        for(int j = 0; j < iCol; ++j) {
            this->strState.push_back(vec2[i][j]);
        }
    }
}

bool CChess::operator < (const CChess &rhs) const
{
    return strState < rhs.strState;
}

bool CChess::operator == (const CChess &rhs) const
{
    return iRow == rhs.iRow && iCol == rhs.iCol && strState == rhs.strState;
}

void CChess::output(ostream &out, const string &colSpace, const string &rowSpace) const
{
	for(int i = 0; i < iRow; ++i) {
        for(int j = 0; j < iCol; ++j) {
        	out << strState[i * iCol + j];
        	if(j != iCol - 1) {
            	out << colSpace;
        	}
        }
        if(i != iRow - 1) {
        	out << rowSpace;
        }
    }
}

std::ostream& operator << (std::ostream &out, const CChess &oChess)
{
    oChess.output(out);
    out << "\n";
    return out;
}

int CChess::astar_f() const
{
    return iSteps;
}

int CChess::astar_g() const
{
    int notMatch = 0;
    for(int i = 0; i < iRow; ++i) {
        for(int j = 0; j < iCol; ++j) {
            if(strState[i * iCol + j] != strStandard[i * iCol + j]) {
                ++notMatch;
            }
        }
    }
    return notMatch;
}

int CChess::astar_h() const
{
    return astar_f() + astar_g();
}

