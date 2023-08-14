#include "Mesh.h"

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	SetupMesh();
}

void Mesh::SetupMesh()
{
	vao = VAO();
	vao.Bind();
	vb = VertexBuffer(vertices.data(), sizeof(vertices));
	indexbuffer = IndexBuffer(indices.data(), indices.size());
	VertexBufferLayout vbLayout;
	vbLayout.Push<float>(3);
	vbLayout.Push<float>(3);
	vbLayout.Push<float>(2);
	vao.AddBuffer(vb, vbLayout);
}

void Mesh::DrawFromMesh(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		//shader.setInt(("material." + name + number).c_str(), i);
		shader.SetUniform1i(name + number, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	vao.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
