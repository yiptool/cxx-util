
#include "macros.h"
#include <typeinfo>
#include <string>

class TypeDescriptor;
typedef const TypeDescriptor * TypeInfo;

template <class TYPE> TypeInfo NOINLINE FCONST typeInfo();

class TypeDescriptor
{
public:
	const std::string name;
	const size_t size;

private:
	TypeDescriptor(const std::type_info & info, size_t sz);

	template <class TYPE> friend TypeInfo typeInfo();
};

template <class TYPE> TypeInfo NOINLINE FCONST typeInfo()
{
	static const TypeDescriptor descriptor(typeid(TYPE), sizeof(TYPE));
	return &descriptor;
}

template <class TYPE> inline FCONST TypeInfo typeInfo(TYPE)
{
	return typeInfo<TYPE>();
}
