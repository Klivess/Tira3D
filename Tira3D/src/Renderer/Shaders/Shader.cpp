#include "Shader.h"
#include "../../Logger/Tira3DLogging.h"
using namespace std;

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != string::npos) {
                //set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos) {
                //set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    ShaderProgramSource source = ShaderProgramSource{};
    source.VertexSource = ss[(int)ShaderType::VERTEX].str();
    source.FragmentSource = ss[(int)ShaderType::FRAGMENT].str();

    if (source.FragmentSource==""&&source.VertexSource=="") {
        Tira3DLogging::LogToConsole("Couldn't find shader! " + filepath);
    }

    return source;
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    //Error Handling
    if (result == GL_FALSE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall(glGetShaderInfoLog(id, 1024, &log_length, message));
        Tira3DLogging::LogToConsole("Failed to compile " + (std::string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader:");
        cout << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT: ") << message << endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    else {
        string dec = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        Tira3DLogging::LogToConsole("Successfully compiled " + dec + " shader.");
    }
    return id;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = Shader::CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, fs));
    GLCall(glAttachShader(program, vs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}