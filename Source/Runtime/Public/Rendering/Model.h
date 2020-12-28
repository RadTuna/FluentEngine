#pragma once

// External Include
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "Resource/Mesh.h"


namespace Fluent
{

	class Model final
	{
	public:
		explicit Model(const std::shared_ptr<Device>& device) noexcept;
		virtual ~Model() = default;

		void CreateModel(const std::vector<VertexPosTexNorTan>& vertices, const std::vector<u32>& indices);
		
		[[nodiscard]]
		const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return mVertexBuffer; }

		[[nodiscard]]
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return mIndexBuffer; }

		[[nodiscard]]
		const std::shared_ptr<Mesh>& GetMesh() const { return mMesh; }

	private:
		void CreateBuffer();
		
	private:
		std::shared_ptr<Mesh> mMesh;

		std::shared_ptr<VertexBuffer> mVertexBuffer;
		std::shared_ptr<IndexBuffer> mIndexBuffer;

		std::shared_ptr<Device> mDevice;
		
	};
	
}
