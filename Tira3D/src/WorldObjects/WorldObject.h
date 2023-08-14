#pragma once
#include <iostream>
#include "../World/World.h"
#include "../Renderer/Shaders/Shader.h"
#include "../Renderer/RenderObjects/VAO.h"
#include "../Renderer/RenderObjects/VertexBuffer.h"
#include "../Renderer/RenderObjects/IndexBuffer.h"
#include "../Renderer/RenderObjects/VertexBufferLayout.h"
#include "../Renderer/Textures/Texture.h"
#include "../World/TiraObjects/TiraObjectsTemplates.h"
#include "ObjectAttributes.h"
#include "../Renderer/Mesh/Model/Model.h"

class WorldObject
{
public:
	std::string objectName;

	WorldTransform currentWorldTransform;

	WorldObject();
	WorldObject(std::string objectName)
		:objectName(objectName), currentWorldTransform(WorldTransform(WorldPosition(), WorldRotation(), WorldScale())) {}

	void SetWorldPosition(WorldPosition position);
	void SetWorldRotation(WorldRotation rotation);
	void SetWorldScale(WorldScale scale);
	void SetWorldTransform(WorldTransform transform);

	void InstantiateObject(WorldPosition worldPos);
	void InstantiateObject(WorldTransform worldPos);

	void LoadTexture(std::string texturePath);

	void SetColour(ObjectColour colour);
	ObjectColour GetColour() { return colour; }

	void DestroyObject();

	void LoadMesh(TiraObjects objectTemplate);
	void LoadMesh(std::string path);

	std::string& GetShaderSource() {
		return shaderSourcePath;
	}

	std::string& GetTextureFile() {
		return textureFile;
	}

	VertexBufferLayout& GetVBLayout() {
		return vbLayout;
	}

	std::vector<float>& GetMeshVerticies() {
		return meshVertices;
	}

	Model& GetObjectMeshModel() {
		return ObjectMeshModel;
	}
private:
	bool ObjectInstantiated;

	VertexBufferLayout vbLayout;
	std::string shaderSourcePath;
	std::string textureFile;
	std::vector<float> meshVertices;
	ObjectColour colour;
	Model ObjectMeshModel;
};
