#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void ShaderProgram::PassFloat(float value, const char *name)
{
    glUniform1f(glGetUniformLocation(m_Id, name), value);
}

void ShaderProgram::PassInt(int value, const char *name)
{
    glUniform1i(glGetUniformLocation(m_Id, name), value);
}

void ShaderProgram::PassVec2(glm::vec2 &value, const char *name)
{
    glUniform2fv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void ShaderProgram::PassVec3(glm::vec3 &value, const char *name)
{
    glUniform3fv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void ShaderProgram::PassVec4(glm::vec4 &value, const char *name)
{
    glUniform4fv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void ShaderProgram::PassIVec2(glm::ivec2 &value, const char *name)
{
    glUniform2iv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void ShaderProgram::PassIVec3(glm::ivec3 &value, const char *name)
{
    glUniform3iv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void ShaderProgram::PassIVec4(glm::ivec4 &value, const char *name)
{
    glUniform4iv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void ShaderProgram::PassMat3(glm::mat3 &value, const char *name)
{
    glUniformMatrix3fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::PassMat4(glm::mat4 &value, const char *name)
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, glm::value_ptr(value));
}
