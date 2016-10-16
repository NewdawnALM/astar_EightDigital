#ifndef  __EXCEPTION_H
#define  __EXCEPTION_H

class CException
{
public:
    CException(int _code = 0, const string &_msg = ""): code(_code), msg(_msg) { }
    int code;
    string msg;
};

#endif
