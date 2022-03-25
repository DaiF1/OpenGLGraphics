#pragma once
#include <glm/fwd.hpp>
#include <string>

class ShaderProgram
{
private:
    unsigned int m_Id;
    unsigned int m_ubo;

public:
    ShaderProgram();
    ShaderProgram(const char *vertexFile, const char *fragmentFile);
    
    bool Load(const char *vertexFile, const char *fragmentFile);
    void Bind();
    void Unbind();
    void Destroy();

    void PassFloat(float value, const char *name);
    void PassInt(int value, const char *name);

    void PassVec2(glm::vec2 &value, const char *name);
    void PassVec3(glm::vec3 &value, const char *name);
    void PassVec4(glm::vec4 &value, const char *name);
    void PassIVec2(glm::ivec2 &value, const char *name);
    void PassIVec3(glm::ivec3 &value, const char *name);
    void PassIVec4(glm::ivec4 &value, const char *name);

    void PassMat3(glm::mat3 &value, const char *name);
    void PassMat4(glm::mat4 &value, const char *name);
};
