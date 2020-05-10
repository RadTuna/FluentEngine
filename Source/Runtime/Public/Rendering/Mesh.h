#pragma once

// External Include
#include <vector>
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "RHI/Vertex.h"
#include "RHI/VertexBuffer.h"
#include "RHI/IndexBuffer.h"


namespace Fluent
{
	
	class Mesh final
	{
	public:

		explicit Mesh() = default;
		~Mesh() = default;

		
		void CreateMesh(const std::vector<VertexPosTex>& vertices, const std::vector<u32>& indices);
		void CreateMesh(const VertexPosTex* vertices, u32 vertexCount, const u32* indices, u32 indexCount);

		[[nodiscard]]
		const std::vector<VertexPosTex>& GetVertices() const { return mVertices; }

		[[nodiscard]]
		const std::vector<u32>& GetIndices() const { return mIndices; }

		[[nodiscard]]
		const VertexPosTex* GetRawVertices() const { return mVertices.data(); }

		[[nodiscard]]
		const u32* GetRawIndices() const { return mIndices.data(); }

		[[nodiscard]]
		u32 GetVerticesNum() const { return static_cast<u32>(mVertices.size()); }
		
		[[nodiscard]]
		u32 GetIndicesNum() const { return static_cast<u32>(mIndices.size()); }
		
	private:

		std::vector<VertexPosTex> mVertices;
		std::vector<u32> mIndices;

	};

}
