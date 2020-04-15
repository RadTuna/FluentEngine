
// Primary Include
#include "Core/ReflectionClass.h"


namespace Fluent
{
	
	ReflectionClass::ReflectionClass(
		ReflectionClass* superClass, 
		u64 classID, 
		const tchar* className,
		u64 classSize)
		: mSuperClass(superClass)
		, mClassID(classID)
		, mClassName(className)
		, mClassSize(classSize)
	{
	}

	void ReflectionClass::SetNewSuper(ReflectionClass* superClass)
	{
		if (superClass)
		{
			mSuperClass = superClass;
		}
	}

	bool ReflectionClass::IsChildOf(ReflectionClass* baseClass)
	{
		if (!baseClass)
		{
			return false;
		}

		bool result = false;
		for (ReflectionClass* loopClass = this; loopClass != nullptr; loopClass = loopClass->GetSuperClass())
		{
			if (loopClass == baseClass)
			{
				result = true;
				break;
			}
		}

		return result;
	}

	bool ReflectionClass::IsEqual(ReflectionClass* baseClass) const
	{
		if (!baseClass)
		{
			return false;
		}

		return mClassID == baseClass->mClassID;
	}
}
