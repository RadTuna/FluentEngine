
// Primary Include
#include "Resource/GeometryGenerator.h"


namespace Fluent
{
	Mesh GeometryGenerator::CreateBox(f32 width, f32 height, f32 depth)
	{
		Mesh outMesh;

		enum { VERTICES_NUM = 24, INDICES_NUM = 36 };
		VertexPosTex vertices[VERTICES_NUM] = {};
		
		const f32 halfWidth = 0.5f * width;
		const f32 halfHeight = 0.5f * height;
		const f32 halfDepth = 0.5f * depth;

		// Fill in the front face vertex data.
		vertices[0] = { Vector4(-halfWidth, -halfHeight, -halfDepth, 1.0f), Vector2(0.0f, 1.0f) };
		vertices[1] = { Vector4(-halfWidth, +halfHeight, -halfDepth, 1.0f), Vector2 (0.0f, 0.0f) };
		vertices[2] = { Vector4(+halfWidth, +halfHeight, -halfDepth, 1.0f), Vector2(1.0f, 0.0f) };
		vertices[3] = { Vector4(+halfWidth, -halfHeight, -halfDepth, 1.0f), Vector2(1.0f, 1.0f) };

		// Fill in the back face vertex data.
		vertices[4] = { Vector4(-halfWidth, -halfHeight, +halfDepth, 1.0f), Vector2(1.0f, 1.0f) };
		vertices[5] = { Vector4(+halfWidth, -halfHeight, +halfDepth, 1.0f), Vector2(0.0f, 1.0f) };
		vertices[6] = { Vector4(+halfWidth, +halfHeight, +halfDepth, 1.0f), Vector2(0.0f, 0.0f) };
		vertices[7] = { Vector4(-halfWidth, +halfHeight, +halfDepth, 1.0f), Vector2(1.0f, 0.0f) };

		// Fill in the top face vertex data.
		vertices[8] = { Vector4(-halfWidth, +halfHeight, -halfDepth, 1.0f), Vector2(0.0f, 1.0f) };
		vertices[9] = { Vector4(-halfWidth, +halfHeight, +halfDepth, 1.0f), Vector2(0.0f, 0.0f) };
		vertices[10] = { Vector4(+halfWidth, +halfHeight, +halfDepth, 1.0f), Vector2(1.0f, 0.0f) };
		vertices[11] = { Vector4(+halfWidth, +halfHeight, -halfDepth, 1.0f), Vector2(1.0f, 1.0f) };

		// Fill in the bottom face vertex data.
		vertices[12] = { Vector4(-halfWidth, -halfHeight, -halfDepth, 1.0f), Vector2(1.0f, 1.0f) };
		vertices[13] = { Vector4(+halfWidth, -halfHeight, -halfDepth, 1.0f), Vector2(0.0f, 1.0f) };
		vertices[14] = { Vector4(+halfWidth, -halfHeight, +halfDepth, 1.0f), Vector2(0.0f, 0.0f) };
		vertices[15] = { Vector4(-halfWidth, -halfHeight, +halfDepth, 1.0f), Vector2(1.0f, 0.0f) };

		// Fill in the left face vertex data.
		vertices[16] = { Vector4(-halfWidth, -halfHeight, +halfDepth, 1.0f), Vector2(0.0f, 1.0f) };
		vertices[17] = { Vector4(-halfWidth, +halfHeight, +halfDepth, 1.0f), Vector2(0.0f, 0.0f) };
		vertices[18] = { Vector4(-halfWidth, +halfHeight, -halfDepth, 1.0f), Vector2(1.0f, 0.0f) };
		vertices[19] = { Vector4(-halfWidth, -halfHeight, -halfDepth, 1.0f), Vector2(1.0f, 1.0f) };

		// Fill in the right face vertex data.
		vertices[20] = { Vector4(+halfWidth, -halfHeight, -halfDepth, 1.0f), Vector2(0.0f, 1.0f) };
		vertices[21] = { Vector4(+halfWidth, +halfHeight, -halfDepth, 1.0f), Vector2(0.0f, 0.0f) };
		vertices[22] = { Vector4(+halfWidth, +halfHeight, +halfDepth, 1.0f), Vector2(1.0f, 0.0f) };
		vertices[23] = { Vector4(+halfWidth, -halfHeight, +halfDepth, 1.0f), Vector2(1.0f, 1.0f) };


		u32 indices[INDICES_NUM] = { 0, };

		// Fill in the front face index data
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 0; indices[4] = 2; indices[5] = 3;

		// Fill in the back face index data
		indices[6] = 4; indices[7] = 5; indices[8] = 6;
		indices[9] = 4; indices[10] = 6; indices[11] = 7;

		// Fill in the top face index data
		indices[12] = 8; indices[13] = 9; indices[14] = 10;
		indices[15] = 8; indices[16] = 10; indices[17] = 11;

		// Fill in the bottom face index data
		indices[18] = 12; indices[19] = 13; indices[20] = 14;
		indices[21] = 12; indices[22] = 14; indices[23] = 15;

		// Fill in the left face index data
		indices[24] = 16; indices[25] = 17; indices[26] = 18;
		indices[27] = 16; indices[28] = 18; indices[29] = 19;

		// Fill in the right face index data
		indices[30] = 20; indices[31] = 21; indices[32] = 22;
		indices[33] = 20; indices[34] = 22; indices[35] = 23;

		outMesh.CreateMesh(vertices, VERTICES_NUM, indices, INDICES_NUM);

		return outMesh;
	}

	Mesh GeometryGenerator::CreateQuad(f32 x, f32 y, f32 width, f32 height, f32 depth)
	{
		Mesh outMesh;
		
		enum { VERTICES_NUM = 4, INDICES_NUM = 6 };
		VertexPosTex vertices[VERTICES_NUM] = {};

		vertices[0] = { Vector4(x, y - height, depth, 1.0f), Vector2(0.0f, 1.0f) };
		vertices[1] = { Vector4(x, y, depth, 1.0f), Vector2(0.0f, 0.0f) };
		vertices[2] = { Vector4(x + width, y, depth, 1.0f), Vector2(1.0f, 0.0f) };
		vertices[3] = { Vector4(x + width, y - height, depth, 1.0f), Vector2(1.0f, 1.0f) };

		u32 indices[INDICES_NUM] = { 0, };

		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 0; indices[4] = 2; indices[5] = 3;

		outMesh.CreateMesh(vertices, VERTICES_NUM, indices, INDICES_NUM);

		return outMesh;
	}
	
}
