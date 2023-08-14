#pragma once
#include "../../Shaders/Shader.h"
#include "../Mesh.h"
#include <string>
#include "../../../vendor/assimp/Importer.hpp"
#include "../../../vendor/assimp/scene.h"
#include "../../../vendor/assimp/postprocess.h"
#include "../../Textures/Texture.h"
using std::string;

class Model
{
private:

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
public:
	std::vector<MeshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	bool gammaCorrection;
	std::string directory;
	std::vector<Mesh> meshes;
	Model();
	void loadModel(std::string path);
};
