#pragma once

// External Include
#include <string>

// Engine Include
#include "TypeDefinition.h"


namespace Fluent
{

	class ReflectionClass final
	{
	public:

		ReflectionClass(ReflectionClass* superClass, u64 classID, const std::string& className, u64 classSize);

	private:

		ReflectionClass* mSuperClass;
		u64 mClassID;
		std::string mClassName;
		u64 mClassSize;
		
	};
	
}
