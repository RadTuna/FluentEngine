#pragma once

#include "Core/Core.h"


namespace Fluent
{

	enum class EResourceType
	{
		Unknown,
		Model
	};

	enum class EResourceLoadState
	{
		Idle,
		Running,
		Complete,
		Fail
	};

	class IResource
	{
		REFLECTION_CLASS_NO_SUPER(IResource)
		
	public:

		explicit IResource(EResourceType resourceType) noexcept : mResourceType(resourceType) {}
		virtual ~IResource() = default;

		// IO virtual function
		virtual bool SaveToFile(const std::string& savePath) = 0;
		virtual bool LoadFromFile(const std::string& loadPath) = 0;

	protected:

		EResourceType mResourceType = EResourceType::Unknown;
		EResourceLoadState mLoadState = EResourceLoadState::Idle;
		
	};
	
}
