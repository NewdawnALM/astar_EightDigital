#include "chess.h"
#include "exception.h"
#include <cstring>
#include <algorithm>
using std::sort;
using std::swap;
#define  For(i,s,t)  for(auto i = (s); i < (t); ++i)

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
    	throw CException(1003, "行列数的乘积应该和字符串的长度相等！");
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

void CChess::check_standard() const
{
    int len = strState.size();
    int len2 = strStandard.size();
    if(len != len2) {
        throw CException(1006, "目标状态的字符长度与当前状态的字符长度不等！");
    }
    bool origin[300];
    memset(origin, false, sizeof origin);
    For(i, 0, len) {
        origin[strState[i]] = true;
    }
    bool standard[300];
    memset(standard, false, sizeof standard);
    For(i, 0, len) {
        standard[strStandard[i]] = true;
    }
    For(i, 0, 300) {
        if(origin[i] != standard[i]) {
            throw CException(1007, "目标状态的字符内容与当前状态的字符内容不等！");
        }
    }
}

CChess::CChess(const string &state, int row, int col, const string &standard):
    strState(state), iRow(row), iCol(col), iSteps(0), pparent(NULL),
    iMoveFromLast(UNKOWN), strStandard(standard)
{
    check_row_col();
	iZeroIdx = strState.find('0');
    check_value();
    if(strStandard == "") {
        strStandard = strState;
        sort(strStandard.begin(), strStandard.end());
    }
    check_standard();
    iNotMatch = countNotMatch();
}

bool CChess::operator < (const CChess &rhs) const
{
    return strState < rhs.strState;
}

bool CChess::operator == (const CChess &rhs) const
{
    return iRow == rhs.iRow && iCol == rhs.iCol && strState == rhs.strState;
}

const string& CChess::getStrState() const
{
    return strState;
}

void CChess::setStrStandard(const string &standard)
{
    strStandard = standard;
    check_standard();
    iNotMatch = countNotMatch();
}

int CChess::countNotMatch() const
{
    int notMatch = 0;
    For(i, 0, iRow) {
        For(j, 0, iCol) {
            if(strState[i * iCol + j] != strStandard[i * iCol + j]) {
                ++notMatch;
            }
        }
    }
    return notMatch;
}

int CChess::countLocalNotMatch(int one, int two) const
{
    int oldNotMatch = 0;
    if(strState[two] != strStandard[one]) {
        ++oldNotMatch;
    }
    if(strState[one] != strStandard[two]) {
        ++oldNotMatch;
    }
    int nowNotMatch = 0;
    if(strState[one] != strStandard[one]) {
        ++nowNotMatch;
    }
    if(strState[two] != strStandard[two]) {
        ++nowNotMatch;
    }
    return this->iNotMatch - oldNotMatch + nowNotMatch;
}

vector<CChess> CChess::getNextState() const
{
    vector<CChess> nextChess;
    // 0上面存在数字，可以下移
    if(iZeroIdx >= iCol) {
        CChess down(*this);
        swap(down.strState[iZeroIdx - iCol], down.strState[iZeroIdx]);
        down.iNotMatch = down.countLocalNotMatch(iZeroIdx - iCol, iZeroIdx);
        // down.iNotMatch = down.countNotMatch();
        down.iZeroIdx -= iCol;
        ++down.iSteps;
        down.pparent = this;
        down.iMoveFromLast = CChess::DOWN;
        nextChess.push_back(down);
    }
    if(iZeroIdx < strState.size() - iCol) {
        CChess up(*this);
        swap(up.strState[iZeroIdx + iCol], up.strState[iZeroIdx]);
        up.iNotMatch = up.countLocalNotMatch(iZeroIdx + iCol, iZeroIdx);
        // up.iNotMatch = up.countNotMatch(); 
        up.iZeroIdx += iCol;
        ++up.iSteps;
        up.pparent = this;
        up.iMoveFromLast = CChess::UP;
        nextChess.push_back(up);
    }
    if(iZeroIdx % iCol != 0) {
        CChess right(*this);
        swap(right.strState[iZeroIdx - 1], right.strState[iZeroIdx]);
        right.iNotMatch = right.countLocalNotMatch(iZeroIdx - 1, iZeroIdx);
        // right.iNotMatch = right.countNotMatch();
        --right.iZeroIdx;
        ++right.iSteps;
        right.pparent = this;
        right.iMoveFromLast = CChess::RIGHT;
        nextChess.push_back(right);
    }
    if((iZeroIdx + 1) % iCol != 0) {
        CChess left(*this);
        swap(left.strState[iZeroIdx + 1], left.strState[iZeroIdx]);
        left.iNotMatch = left.countLocalNotMatch(iZeroIdx + 1, iZeroIdx);
        // left.iNotMatch = left.countNotMatch();
        ++left.iZeroIdx;
        ++left.iSteps;
        left.pparent = this;
        left.iMoveFromLast = CChess::LEFT;
        nextChess.push_back(left);
    }
    return nextChess;
}

int CChess::astar_f() const
{
    return iSteps;
}

int CChess::astar_g() const
{
    return iNotMatch;
}

int CChess::astar_h() const
{
    return astar_f() + astar_g();
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

