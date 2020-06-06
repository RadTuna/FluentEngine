#pragma once

// External Include
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "Rendering/Mesh.h"
#include "Resource/IResource.h"


namespace Fluent
{

	class Model final : public IResource
	{
	public:

		explicit Model(const std::shared_ptr<Device>& device) noexcept;
		virtual ~Model() = default;


		// IResource implementation
		bool SaveToFile(const std::string& savePath) override;
		bool LoadFromFile(const std::string& loadPath) override;

		void CreateModel(const std::vector<VertexPosTexNorTan>& vertices, const std::vector<u32>& indices);
		
		[[nodiscard]]
		const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return mVertexBuffer; }

		[[nodiscard]]
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return mIndexBuffer; }

	private:

		void CreateBuffer();
		
	private:

		std::shared_ptr<Mesh> mMesh;

		std::shared_ptr<VertexBuffer> mVertexBuffer;
		std::shared_ptr<IndexBuffer> mIndexBuffer;

		std::shared_ptr<Device> mDevice;
		
	};
	
}
