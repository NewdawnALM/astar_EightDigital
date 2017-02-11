#ifndef __MYFUNCTION_H
#define __MYFUNCTION_H

#include <sstream>
#include <string>
#include <vector>

namespace ALM {

template<typename T1, typename T2>
inline const T2 transType(const T1 &x)
{
	std::stringstream ss;
	ss << x;
	T2 ret;
	ss >> ret;
	return ret;
}

template<typename T>
const std::string vec2ToStr(const std::vector<std::vector<T>> &vec2, const std::string &colSeparator=" ", const std::string &rowSeparator="\n")
{
	std::stringstream ss;
	auto ilen = vec2.size();
	for(auto i = 0; i < ilen; ++i) {
		auto jlen = vec2[i].size();
		for(auto j = 0; j < jlen; ++j) {
			ss << vec2[i][j] << colSeparator;
		}
		ss << rowSeparator;
	}
	return ss.str();
}

}

#endif
