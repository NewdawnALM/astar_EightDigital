#ifndef  __TIMEVAL_H
#define  __TIMEVAL_H

#include <sys/time.h>
#include <iostream>
using std::ostream;

class CTimeVal
{
    friend ostream& operator << (ostream &, const CTimeVal &);
public:
    CTimeVal();
    CTimeVal(const timeval &_tv);
    CTimeVal(const CTimeVal &rhs);
    CTimeVal& operator = (const CTimeVal &rhs);
    bool operator < (const CTimeVal &rhs) const;
    CTimeVal operator - (const CTimeVal &rhs) const;
    /**
     * [costTime description]
     * @return return the cost time(millsecond in default).
     */
    long long costTime(int type=MILL) const;
    /**
     * reset the time with this moment.
     */
    void reset();

    long long toSeconds() const;
    long long toMillSeconds() const;
    long long toMicroSeconds() const;

    enum TIMETYPE
    {
        SECOND, MILL, MICRO
    };
private:
    void setTimeVal(const timeval &_tv);
    timeval tv;
};

#endif
