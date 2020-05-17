
// Primary Include
#include "Rendering/Mesh.h"


namespace Fluent
{
	
	void Mesh::CreateMesh(const std::vector<VertexPosTex>& vertices, const std::vector<u32>& indices)
	{
		mVertices = vertices;
		mIndices = indices;
	}

	void Mesh::CreateMesh(const VertexPosTex* vertices, u32 vertexCount, const u32* indices, u32 indexCount)
	{
		mVertices.clear();
		mVertices.reserve(vertexCount);
		mVertices.assign(&vertices[0], &vertices[vertexCount]);


		mIndices.clear();
		mIndices.reserve(indexCount);
		mIndices.assign(&indices[0], &indices[indexCount]);

	}

	void Mesh::CreateBuffers(std::shared_ptr<Device>& device)
	{
		Assert(mVertices.empty() == false);
		Assert(mIndices.empty() == false);

		mVertexBuffer = std::make_shared<VertexBuffer>(device);
		mIndexBuffer = std::make_shared<IndexBuffer>(device);
		
		mVertexBuffer->CreateBuffer(mVertices);
		mIndexBuffer->CreateBuffer(mIndices);
	}
}
