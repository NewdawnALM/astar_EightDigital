#include "exception.h"

CException::CException(int _code, const string &_msg):
	code(_code), msg(_msg) { }
