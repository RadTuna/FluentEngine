
// Primary Include
#include "Rendering/Model.h"

// Engine Include
#include "RHI/VertexBuffer.h"
#include "RHI/IndexBuffer.h"


namespace Fluent
{
	Model::Model(const std::shared_ptr<Device>& device) noexcept
		: mDevice(device)
	{
		mMesh = std::make_shared<Mesh>();
	}

	void Model::CreateModel(const std::vector<VertexPosTexNorTan>& vertices, const std::vector<u32>& indices)
	{
		mMesh->CreateMesh(vertices, indices);
		CreateBuffer();
	}

	void Model::CreateBuffer()
	{
		mVertexBuffer = std::make_shared<VertexBuffer>(mDevice);
		mVertexBuffer->CreateBuffer(mMesh->GetVertices());

		mIndexBuffer = std::make_shared<IndexBuffer>(mDevice);
		mIndexBuffer->CreateBuffer(mMesh->GetIndices());
	}

}
