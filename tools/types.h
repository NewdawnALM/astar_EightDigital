#ifndef __TYPE_H
#define __TYPE_H

namespace ALM
{
namespace types
{
	typedef int int32;
	typedef unsigned int uint32;

	const uint32 MAX_UINT32 = ~(uint32(0));
	const uint32 MAX_INT32 = int32(MAX_UINT32 >> 1);

	typedef long long int64;
	typedef unsigned long long uint64;

	const uint64 MAX_UINT64 = ~(uint64(0));
	const int64 MAX_INT64 = int64(MAX_UINT64 >> 1);

	enum JSONTYPE
	{
		JNULL = 0, JBOOL, JINT, JUINT, JINT64, JUINT64, JDOUBLE, JSTRING
	};
}
}

#endif
