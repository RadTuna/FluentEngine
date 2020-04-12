#pragma once

// External Include
#include <map>

// Engine Include
#include "Core/Core.h"


#define REGISTER_COMPONENT() \
	inline static u64 mID = GenerateFID(); \
	bool IsEqual(u64 id) \
	{ \
		return mID == id; \
	} \

namespace Fluent
{
	
	class IComponent
	{
	public:

		explicit IComponent() = default;
		virtual ~IComponent() = default;

	};
	
}
