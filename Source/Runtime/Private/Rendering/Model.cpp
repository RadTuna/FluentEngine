
// Primary Include
#include "Rendering/Model.h"


namespace Fluent
{
	Model::Model(const std::shared_ptr<Device>& device) noexcept
		: IResource(EResourceType::Model)
		, mDevice(device)
	{
	}

	bool Model::SaveToFile(const std::string& savePath)
	{
	}

	bool Model::LoadFromFile(const std::string& loadPath)
	{
	}

	void Model::CreateModel()
	{
	}
}
