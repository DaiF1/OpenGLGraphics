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

bool Shader::Load(ShaderType type, const char *filePath)
{
    GLenum t = (type == ShaderType::VERTEX) ? 
        GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    
    std::ifstream file(filePath);
    std::string str((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());
    const char *content = str.c_str();

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

ShaderProgram::ShaderProgram()
{}

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    Load(vertexFile, fragmentFile);
}

bool ShaderProgram::Load(const char *vertexFile, const char *fragmentFile)
{
    /*
    Shader vertex;   
    Shader fragment;

    if (!vertex.Load(ShaderType::VERTEX, vertexFile))
        return false;
    if (!vertex.Load(ShaderType::FRAGMENT, fragmentFile))
        return false;

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
    */

    std::ifstream vert(vertexFile);
    std::string strv((std::istreambuf_iterator<char>(vert)), 
            std::istreambuf_iterator<char>());
    const char *vertexContent = strv.c_str();

    std::ifstream frag(fragmentFile);
    std::string strf((std::istreambuf_iterator<char>(frag)), 
            std::istreambuf_iterator<char>());
    const char *fragmentContent = strf.c_str();

    unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexContent, NULL);
    glCompileShader(vertexId);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
        std::cout << "[Error] Failed to Compile Vertex Shader:\n" 
            << infoLog << std::endl;
        return false;
    }
    
    // fragment shader
    unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentContent, NULL);
    glCompileShader(fragmentId);

    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
        std::cout << "[Error] Failed to Compile Fragment Shader:\n" 
            << infoLog << std::endl;
        return false;
    }

    // link shaders
    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertexId);
    glAttachShader(m_Id, fragmentId);
    glLinkProgram(m_Id);
    // check for linking errors
    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
        std::cout << "[Error] Failed to Link Shaders:\n" 
            << infoLog << std::endl;
    }
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void ShaderProgram::Bind()
{
    glUseProgram(m_Id);
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::Destroy()
{
    glDeleteProgram(m_Id);
}
