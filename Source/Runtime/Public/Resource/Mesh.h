#pragma once

// External Include
#include <vector>
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "RHI/Vertex.h"
#include "Resource/IResource.h"


namespace Fluent
{
	
	class Mesh final : IResource
	{
	public:

		explicit Mesh() noexcept;
		~Mesh() = default;

		// IResource interface implementation
		bool SaveToFile(const std::string& savePath) override;
		bool LoadFromFile(const std::string& loadPath) override;
		
		void CreateMesh(const std::vector<VertexPosTexNorTan>& vertices, const std::vector<u32>& indices);
		void CreateMesh(const VertexPosTexNorTan* vertices, u32 vertexCount, const u32* indices, u32 indexCount);

		[[nodiscard]]
		const std::vector<VertexPosTexNorTan>& GetVertices() const { return mVertices; }

		[[nodiscard]]
		const std::vector<u32>& GetIndices() const { return mIndices; }

		[[nodiscard]]
		const VertexPosTexNorTan* GetRawVertices() const { return mVertices.data(); }

		[[nodiscard]]
		const u32* GetRawIndices() const { return mIndices.data(); }

		[[nodiscard]]
		u32 GetVerticesNum() const { return static_cast<u32>(mVertices.size()); }
		
		[[nodiscard]]
		u32 GetIndicesNum() const { return static_cast<u32>(mIndices.size()); }
		
	private:

		std::vector<VertexPosTexNorTan> mVertices;
		std::vector<u32> mIndices;
		
	};

}
