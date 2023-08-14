#include "../../vendor/glm/fwd.hpp"
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtc/matrix_transform.hpp"
#include "../../vendor/glm/gtc/type_ptr.hpp"
#include "../RenderObjects/VAO.h"
#include <string>
#include "../RenderObjects/IndexBuffer.h"
#include <vector>
#include "../Shaders/Shader.h"


#define MAX_BONE_INFLUENCE 4

struct MeshVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct MeshTexture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	// mesh data
	std::vector<MeshVertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<MeshTexture>      textures;
	Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
	void DrawFromMesh(Shader& shader);
	void SetupMesh();

private:
	VAO vao;
	IndexBuffer indexbuffer;
	VertexBuffer vb;
};