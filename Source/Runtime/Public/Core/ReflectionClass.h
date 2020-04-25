#pragma once

// Engine Include
#include "TypeDefinition.h"
#include "ReflectionProperty.h"


namespace Fluent
{

	class ReflectionClass final
	{
	public:

		ReflectionClass(ReflectionClass* superClass, u64 classID, const tchar* className, u64 classSize);
		~ReflectionClass() = default;
		

		void SetNewSuper(ReflectionClass* superClass);

		void AddProperty(ReflectionProperty* property);

		template<typename Class>
		bool IsChildOf()
		{
			return IsChildof(Class::GetClass());
		}
		bool IsChildOf(ReflectionClass* baseClass);
		
		[[nodiscard]]
		bool IsEqual(ReflectionClass* baseClass) const;
		[[nodiscard]]
		bool IsEqual(u64 classID) const { return mClassID == classID; }

		[[nodiscard]]
		ReflectionClass* GetSuperClass() const { return mSuperClass; }
		
		[[nodiscard]]
		u64 GetClassID() const { return mClassID; }

		[[nodiscard]]
		const tchar* GetClassName() const { return mClassName; }

		[[nodiscard]]
		u64 GetClassSize() const { return mClassSize; }
		
	private:

		ReflectionProperty* mFrontProperty = nullptr;
		
		ReflectionClass* mSuperClass = nullptr;
		u64 mClassID = 0;
		const tchar* mClassName;
		u64 mClassSize = 0;
		
	};
	
}
