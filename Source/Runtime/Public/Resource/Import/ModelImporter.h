#pragma once

// Engine Include
#include "Core/Core.h"
#include "Rendering/Model.h"

// External Include
#include <vector>

struct aiScene;
struct aiNode;
struct aiMesh;

namespace Fluent
{

	constexpr i32 TRIANGLE_LIMIT = INT32_MAX;
	constexpr i32 VERTEX_LIMIT = INT32_MAX;
	constexpr f32 MAX_NORMAL_SMOOTH_ANGLE = 80.0f;
	constexpr f32 MAX_TANGENT_SMOOTH_ANGLE = 80.0f;
	
	class ModelImporter final
	{
	public:

		explicit ModelImporter() = default;
		~ModelImporter() = default;

		bool Load(const std::string& destPath, const std::string& srcPath);
		
	private:

		void ParseNode(const aiScene* scene, const aiNode* node);
		void ParseNodeMeshes(const aiScene* scene, const aiNode* node);
		void LoadMesh(aiMesh* mesh);

	private:

		std::vector<Model> mModels;
		
	};
}
