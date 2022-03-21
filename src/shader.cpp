#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram()
{}

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    Load(vertexFile, fragmentFile);
}

bool ShaderProgram::Load(const char *vertexFile, const char *fragmentFile)
{
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
