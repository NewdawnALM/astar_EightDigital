#ifndef  __TIMEVAL_H
#define  __TIMEVAL_H

#include <sys/time.h>
#include <iostream>
using std::ostream;

class CTimeVal
{
    friend ostream& operator << (ostream &, const CTimeVal &);
public:
    CTimeVal() {  gettimeofday(&tv, NULL);  }
    CTimeVal(const timeval &_tv) {  setTimeVal(_tv);  }
    CTimeVal(const CTimeVal &rhs) {  setTimeVal(rhs.tv);  }
    CTimeVal& operator = (const CTimeVal &rhs) {   setTimeVal(rhs.tv);  return *this;  }
    bool operator < (const CTimeVal &rhs) const {
        if(tv.tv_sec == rhs.tv.tv_sec)   return tv.tv_usec < rhs.tv.tv_usec;
        return tv.tv_sec < rhs.tv.tv_sec;
    }
    CTimeVal operator - (const CTimeVal &rhs) const {
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
    long long toSeconds() const {  return tv.tv_sec;  }
    long long toMillSeconds() const {  return tv.tv_sec * 1000 + tv.tv_usec / 1000;  }
    long long toMicroSeconds() const {  return tv.tv_sec * 1000000 + tv.tv_usec;  }
private:
    void setTimeVal(const timeval &_tv) {  tv.tv_sec = _tv.tv_sec;  tv.tv_usec = _tv.tv_usec;  }
    timeval tv;
};

// ostream& operator << (ostream &out, const CTimeVal &otime)
// {
//     out << otime.tv.tv_sec << "  " << otime.tv.tv_usec;
//     return out;
// }

#endif
