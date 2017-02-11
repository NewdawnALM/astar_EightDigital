#include "timeval.h"

CTimeVal::CTimeVal()
{
	gettimeofday(&tv, NULL);
}

CTimeVal::CTimeVal(const timeval &_tv)
{
	setTimeVal(_tv);
}

CTimeVal::CTimeVal(const CTimeVal &rhs)
{
	setTimeVal(rhs.tv);
}

CTimeVal& CTimeVal::operator = (const CTimeVal &rhs)
{
	setTimeVal(rhs.tv);  return *this;
}

void CTimeVal::setTimeVal(const timeval &_tv)
{
    tv.tv_sec = _tv.tv_sec;  tv.tv_usec = _tv.tv_usec;
}

bool CTimeVal::operator < (const CTimeVal &rhs) const
{
    if(tv.tv_sec == rhs.tv.tv_sec) {
    	return tv.tv_usec < rhs.tv.tv_usec;
    }
    return tv.tv_sec < rhs.tv.tv_sec;
}

CTimeVal CTimeVal::operator - (const CTimeVal &rhs) const
{
    CTimeVal sub;
    if(rhs < *this) {
        sub.tv.tv_sec = tv.tv_sec - rhs.tv.tv_sec;
        sub.tv.tv_usec = tv.tv_usec - rhs.tv.tv_usec;
    } else {
        sub.tv.tv_sec = rhs.tv.tv_sec - tv.tv_sec;
        sub.tv.tv_usec = rhs.tv.tv_usec - tv.tv_usec;
    }
    if(sub.tv.tv_usec < 0) {
        --sub.tv.tv_sec;
        sub.tv.tv_usec += 1000000;
    }
    return sub;
}

/**
 * [costTime description]
 * @return return the cost time(millisecond in default).
 */
CTimeVal::int64 CTimeVal::costTime(int type) const
{
    auto diff = CTimeVal() - *this;
	if(type == SECOND) {
        return diff.toSeconds();
    } else if(type == MICRO) {
        return diff.toMicroSeconds();
    } else {
        return diff.toMilliSeconds();
    }
}

/**
 * reset the time with this moment.
 */
void CTimeVal::reset()
{
	gettimeofday(&tv, NULL);
}

CTimeVal::int64 CTimeVal::toSeconds() const
{
	return tv.tv_sec;
}

CTimeVal::int64 CTimeVal::toMilliSeconds() const
{
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

CTimeVal::int64 CTimeVal::toMicroSeconds() const
{
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

ostream& operator << (ostream &out, const CTimeVal &otime)
{
    out << otime.tv.tv_sec << "  " << otime.tv.tv_usec;
    return out;
}
