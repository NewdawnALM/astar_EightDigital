#ifndef  __EXCEPTION_H
#define  __EXCEPTION_H

#include <string>
using std::string;

class CException
{
public:
    CException(int _code = 0, const string &_msg = "");
    int code;
    string msg;
};

#endif
