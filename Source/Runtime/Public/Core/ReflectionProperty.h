#pragma once

// Engine Include
#include "Core/TypeDefinition.h"


namespace Fluent
{

	class ReflectionProperty final
	{
	public:

		ReflectionProperty(const tchar* typeName, const tchar* propertyName, u64 size);
		~ReflectionProperty() = default;


		void SetNext(ReflectionProperty* property);
		
		[[nodiscard]]
		ReflectionProperty* GetNext() const { return mNextProperty; }

		[[nodiscard]]
		const tchar* GetTypeName() const { return mTypeName; }

		[[nodiscard]]
		const tchar* GetPropertyName() const { return mPropertyName; }

		[[nodiscard]]
		u64 GetPropertySize() const { return mPropertySize; }
		
	private:

		ReflectionProperty* mNextProperty = nullptr;

		const tchar* mTypeName = nullptr;
		const tchar* mPropertyName = nullptr;
		u64 mPropertySize = 0;
		
	};
	
}
