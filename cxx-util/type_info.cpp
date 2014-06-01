#include "type_info.h"

#ifdef __GNUG__

#include <cxxabi.h>
#include <cstdlib>

namespace
{
	struct nameptr
	{
		char * p;
		inline nameptr(char * ptr) : p(ptr) {}
		inline ~nameptr() { free(p); }
	};
}

static std::string unmangleName(const char * name)
{
	int status = -1;
	nameptr ptr(abi::__cxa_demangle(name, nullptr, nullptr, &status));
	return (status == 0 ? ptr.p : name);
}

#else // __GNUG__

static std::string unmangleName(const char * name)
{
	return name;
}

#endif // __GNUG__

TypeDescriptor::TypeDescriptor(const std::type_info & info, size_t sz)
	: name(unmangleName(info.name())),
	  size(sz)
{
}
