
// Primary Include
#include "Core/ReflectionClass.h"


namespace Fluent
{
	
	ReflectionClass::ReflectionClass(
		ReflectionClass* superClass, 
		u64 classID, 
		const std::string& className,
		u64 classSize)
		: mSuperClass(superClass)
		, mClassID(classID)
		, mClassName(className)
		, mClassSize(classSize)
	{
	}
}
