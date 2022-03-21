#pragma once
#include <string>

class ShaderProgram
{
private:
    unsigned int m_Id;

public:
    ShaderProgram();
    ShaderProgram(const char *vertexFile, const char *fragmentFile);
    
    bool Load(const char *vertexFile, const char *fragmentFile);
    void Bind();
    void Unbind();
    void Destroy();
};
