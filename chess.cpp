#include "chess.h"
#include "exception.h"
#include <cstring>
#include <algorithm>
using std::sort;
using std::swap;
#define  For(i,s,t)  for(auto i = (s); i != (t); ++i)

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
    strState(state), iRow(row), iCol(col), CState(),
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

void CChess::checkSomeFields(const CState &rhs) const
{
    if(iRow != ((CChess*)&rhs)->iRow) {
        throw CException(2001, "开始字符串和结束字符串的行不相同！");
    }
    if(iCol != ((CChess*)&rhs)->iCol) {
        throw CException(2002, "开始字符串和结束字符串的列不相同！");
    }
    auto tmp_this = strState;
    auto tmp_rhs = ((CChess*)&rhs)->strState;
    sort(tmp_this.begin(), tmp_this.end());
    sort(tmp_rhs.begin(), tmp_rhs.end());
    if(tmp_this != tmp_rhs) {
        throw CException(2003, "开始字符串和结束字符串含有的字符有差别！");
    }
}

bool CChess::operator < (const CState &rhs) const
{
    const auto &r_str = ((CChess*)&rhs)->strState;
    int cmp = strcmp(strState.c_str(), r_str.c_str());
    const auto &r_row = ((CChess*)&rhs)->iRow;
    const auto &r_col = ((CChess*)&rhs)->iCol;
    if(cmp == 0) {
        if(iRow == r_row)   return iCol < r_col;
        return iRow < r_row;
    }
    return cmp < 0;
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

vector<CState*> CChess::getNextState() const
{
    vector<CState*> nextChess;
    // 0上面存在数字，可以下移
    if(iZeroIdx >= iCol) {
        CChess *down = new CChess(*this);
        swap(down->strState[iZeroIdx - iCol], down->strState[iZeroIdx]);
        down->iNotMatch = down->countLocalNotMatch(iZeroIdx - iCol, iZeroIdx);
        down->iZeroIdx -= iCol;
        down->iMoveFromLast = CChess::DOWN;
        nextChess.push_back(down);
    }
    if(iZeroIdx < strState.size() - iCol) {
        CChess *up = new CChess(*this);
        swap(up->strState[iZeroIdx + iCol], up->strState[iZeroIdx]);
        up->iNotMatch = up->countLocalNotMatch(iZeroIdx + iCol, iZeroIdx);
        up->iZeroIdx += iCol;
        up->iMoveFromLast = CChess::UP;
        nextChess.push_back(up);
    }
    if(iZeroIdx % iCol != 0) {
        CChess *right = new CChess(*this);
        swap(right->strState[iZeroIdx - 1], right->strState[iZeroIdx]);
        right->iNotMatch = right->countLocalNotMatch(iZeroIdx - 1, iZeroIdx);
        --right->iZeroIdx;
        right->iMoveFromLast = CChess::RIGHT;
        nextChess.push_back(right);
    }
    if((iZeroIdx + 1) % iCol != 0) {
        CChess *left = new CChess(*this);
        swap(left->strState[iZeroIdx + 1], left->strState[iZeroIdx]);
        left->iNotMatch = left->countLocalNotMatch(iZeroIdx + 1, iZeroIdx);
        ++left->iZeroIdx;
        left->iMoveFromLast = CChess::LEFT;
        nextChess.push_back(left);
    }
    return nextChess;
}

size_t CChess::astar_g() const
{
    return iNotMatch;
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

