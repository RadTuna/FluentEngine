
// Primary Include
#include "Resource/Import/ModelImporter.h"

// External Include
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>

namespace Fluent
{
	ModelImporter::ModelImporter(const std::shared_ptr<Device>& device) noexcept
		: mDevice(device)
	{
	}

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

		for (Model& model : mModels)
		{
			model.SaveToFile(destPath);
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
		for (u32 i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			LoadMesh(mesh);
		}
	}

	void ModelImporter::LoadMesh(aiMesh* mesh)
	{
		const u32 vertexCount = mesh->mNumVertices;
		const u32 indexCount = mesh->mNumFaces * 3;

		std::vector<VertexPosTexNorTan> vertices;
		vertices.resize(vertexCount);
		for (u32 i = 0; i < vertexCount; ++i)
		{
			VertexPosTexNorTan& vertex = vertices[i];
			
			if (mesh->HasPositions())
			{
				aiVector3D& position = mesh->mVertices[i];
				vertex.Position.mX = position.x;
				vertex.Position.mY = position.y;
				vertex.Position.mZ = position.z;
				vertex.Position.mW = 1.0f;
			}

			if (mesh->HasNormals())
			{
				aiVector3D& normal = mesh->mNormals[i];
				vertex.Normal.mX = normal.x;
				vertex.Normal.mY = normal.y;
				vertex.Normal.mZ = normal.z;
			}

			if (mesh->HasTangentsAndBitangents())
			{
				aiVector3D& tangent = mesh->mTangents[i];
				vertex.Tangent.mX = tangent.x;
				vertex.Tangent.mY = tangent.y;
				vertex.Tangent.mZ = tangent.z;

				aiVector3D& biTangent = mesh->mBitangents[i];
				vertex.BiTangent.mX = biTangent.x;
				vertex.BiTangent.mY = biTangent.y;
				vertex.BiTangent.mZ = biTangent.z;
			}

			const u32 uvChannelsNum = 0;
			if (mesh->HasTextureCoords(uvChannelsNum))
			{
				aiVector3D& texCoord = mesh->mTextureCoords[uvChannelsNum][i];
				vertex.TexCoord.mX = texCoord.x;
				vertex.TexCoord.mY = texCoord.y;
			}
		}

		std::vector<u32> indices;
		indices.resize(indexCount);
		for (u32 i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace& face = mesh->mFaces[i];
			const u32 currentIndex = i * 3;
			indices[currentIndex + 0] = face.mIndices[0];
			indices[currentIndex + 1] = face.mIndices[1];
			indices[currentIndex + 2] = face.mIndices[2];
		}

		Model& model = mModels.emplace_back(mDevice);
		model.CreateModel(vertices, indices);
	}

}
