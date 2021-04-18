#pragma once


#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


#include "MeshModel.h"
#include "TextureMapping.h"

class ImportedModel
{
public:
	ImportedModel();

	void LoadModel(const std::string& fileName);
	void RenderModel();
	void ClearModel();

	~ImportedModel();

private:

	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

	std::vector<MeshModel*> meshList;
	std::vector<TextureMapping*> textureList;
	std::vector<unsigned int> meshToTex;
};

