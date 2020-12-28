#pragma once

#include "Core/Core.h"


namespace Fluent
{

	enum class EResourceType
	{
		Unknown,
		Mesh,
		Texture,
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
