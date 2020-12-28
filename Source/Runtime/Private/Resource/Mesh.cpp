
// Primary Include
#include "Resource/Mesh.h"


namespace Fluent
{
    Mesh::Mesh() noexcept
		: IResource(EResourceType::Mesh)
    {
    }

    bool Mesh::SaveToFile(const std::string& savePath)
    {
		// pass
		return false;
    }

    bool Mesh::LoadFromFile(const std::string& loadPath)
    {
		// pass
		return false;
    }

    void Mesh::CreateMesh(const std::vector<VertexPosTexNorTan>& vertices, const std::vector<u32>& indices)
	{
		mVertices = vertices;
		mIndices = indices;
	}

	void Mesh::CreateMesh(const VertexPosTexNorTan* vertices, u32 vertexCount, const u32* indices, u32 indexCount)
	{
		mVertices.clear();
		mVertices.reserve(vertexCount);
		mVertices.assign(&vertices[0], &vertices[vertexCount]);

		mIndices.clear();
		mIndices.reserve(indexCount);
		mIndices.assign(&indices[0], &indices[indexCount]);
	}
	
}
