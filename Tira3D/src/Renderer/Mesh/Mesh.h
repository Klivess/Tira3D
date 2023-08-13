#include "src/vendor/glm/fwd.hpp"
#include "src/vendor/glm/glm.hpp"
#include "src/vendor/glm/gtc/matrix_transform.hpp"
#include "src/vendor/glm/gtc/type_ptr.hpp"
#include <string>
#include <vector>

struct MeshVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct MeshTexture {
	unsigned int id;
	std::string type;
};

class Mesh {
public:
	// mesh data
	std::vector<MeshVertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<MeshTexture>      textures;
	Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
private:
	void SetupMesh();
};