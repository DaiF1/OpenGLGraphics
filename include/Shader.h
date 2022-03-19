#pragma once

enum ShaderType
{
    VERTEX,
    FRAGMENT
};

class Shader
{
private:
    char *m_filePath;
    unsigned int m_Id;

    const char *ParseFile(const char *path);

public:
    ShaderType type;

    Shader();
    Shader(ShaderType type, const char *filePath);

    bool Load(ShaderType type, const char *filePath);
    void Destroy();
};

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
