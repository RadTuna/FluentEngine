
// Primary Include
#include "Resource/Import/ModelImporter.h"

// External Include
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>

namespace Fluent
{

	bool ModelImporter::Load(const std::string& destPath, const std::string& srcPath)
	{
		Assimp::Importer importer;

		importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, MAX_NORMAL_SMOOTH_ANGLE);
		importer.SetPropertyFloat(AI_CONFIG_PP_CT_MAX_SMOOTHING_ANGLE, MAX_TANGENT_SMOOTH_ANGLE);
		importer.SetPropertyInteger(AI_CONFIG_PP_SLM_TRIANGLE_LIMIT, TRIANGLE_LIMIT);
		importer.SetPropertyInteger(AI_CONFIG_PP_SLM_VERTEX_LIMIT, VERTEX_LIMIT);
		importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);

		int importerFlags =
			aiProcess_CalcTangentSpace | 
			aiProcess_GenSmoothNormals | 
			aiProcess_JoinIdenticalVertices |
			aiProcess_OptimizeMeshes |
			aiProcess_ImproveCacheLocality |
			aiProcess_RemoveComponent |
			aiProcess_SplitLargeMeshes |
			aiProcess_Triangulate |
			aiProcess_GenUVCoords |
			aiProcess_SortByPType |
			aiProcess_FindDegenerates |
			aiProcess_FindInvalidData |
			aiProcess_FindInstances |
			aiProcess_ValidateDataStructure |
			aiProcess_Debone |
			aiProcess_ConvertToLeftHanded;

		const aiScene* scene = importer.ReadFile(srcPath.c_str(), importerFlags);
		if (scene != nullptr)
		{
			mModels.reserve(scene->mNumMeshes);
			ParseNode(scene, scene->mRootNode);
		}

		importer.FreeScene();
		return scene != nullptr;
	}

	void ModelImporter::ParseNode(const aiScene* scene, const aiNode* node)
	{
		ParseNodeMeshes(scene, node);
		
		for (u32 i = 0; i < node->mNumChildren; ++i)
		{
			ParseNode(scene, node->mChildren[i]);
		}
	}

	void ModelImporter::ParseNodeMeshes(const aiScene* scene, const aiNode* node)
	{
		for (u32 i = 0; i < node->mMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			LoadMesh(mesh);
		}
	}

	void ModelImporter::LoadMesh(aiMesh* mesh)
	{
		const u32 vertexCount = mesh->mNumVertices;
		const u32 indexCount = mesh->mNumFaces * 3;

		std::vector<VertexPosTex>
	}



}
