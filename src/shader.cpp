#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

Shader::Shader()
{}

Shader::Shader(ShaderType type, const char *filePath)
{
    Load(type, filePath);
}

std::string Shader::ParseFile(const char *path)
{
    std::ifstream file(path);
    std::string str((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());
    return str;
}

bool Shader::Load(ShaderType type, const char *filePath)
{
    GLenum t = (type == ShaderType::VERTEX) ? 
        GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

    const char *content = ParseFile(filePath).c_str();

    id = glCreateShader(t);
    glShaderSource(id, 1, &content, NULL);
    glCompileShader(id);

    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        const char *stype = (type == ShaderType::VERTEX) ? 
            "Vertex" : "Fragment";
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "[Error] Failed to Compile " << stype <<
            " Shader:\n" << infoLog << std::endl;
        return false;
    }

    return true;
}

void Shader::Destroy()
{
    glDeleteShader(id);
}

bool ShaderProgram::Load(const char *vertexFile, const char *fragmentFile)
{
    Shader vertex(ShaderType::VERTEX, vertexFile);   
    Shader fragment(ShaderType::FRAGMENT, fragmentFile);

    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertex.id);
    glAttachShader(m_Id, fragment.id);
    glLinkProgram(m_Id);

    int success;
    char infoLog[512];
    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_Id, 512, NULL, infoLog);
        std::cout << "[Error] Failed to Link Shaders:\n" << 
            infoLog << std::endl;
        return false;
    }

    vertex.Destroy();
    fragment.Destroy();
    return true;
}

void ShaderProgram::Bind()
{
    glUseProgram(m_Id);
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}
