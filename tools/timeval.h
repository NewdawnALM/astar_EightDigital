#ifndef  __TIMEVAL_H
#define  __TIMEVAL_H

#include <sys/time.h>
#include <iostream>
using std::ostream;
#include "types.h"

class CTimeVal
{
    friend ostream& operator << (ostream &, const CTimeVal &);
    typedef ALM::types::int64 int64;
public:
    CTimeVal();
    CTimeVal(const timeval &_tv);
    CTimeVal(const CTimeVal &rhs);
    CTimeVal& operator = (const CTimeVal &rhs);
    bool operator < (const CTimeVal &rhs) const;
    CTimeVal operator - (const CTimeVal &rhs) const;
    /**
     * [costTime description]
     * @return return the cost time(millisecond in default).
     */
    int64 costTime(int type=MILL) const;
    /**
     * reset the time with this moment.
     */
    void reset();

    int64 toSeconds() const;
    int64 toMilliSeconds() const;
    int64 toMicroSeconds() const;

    enum TIMETYPE
    {
        SECOND, MILL, MICRO
    };
private:
    void setTimeVal(const timeval &_tv);
    timeval tv;
};

#endif
