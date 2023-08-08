#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../../vendor/glew.h"
#include "../../vendor/glfw3.h"
#include <unordered_map>
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtc/matrix_transform.hpp"
#include "../../vendor/glm/gtc/type_ptr.hpp"


struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_shaderFilepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, unsigned int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
public:
	Shader(const std::string& filepath)
		: m_shaderFilepath(filepath), m_RendererID(0)
	{
		ShaderProgramSource source = ParseShader(filepath);
		m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	}
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void SetUniformMatrix4fv(const std::string& name, glm::mat4 matrix);
	void SetModelViewProjection(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};

