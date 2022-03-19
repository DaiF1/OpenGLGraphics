#pragma once
#include <vector>
#include <array>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex
{
    std::array<float, 4> color;
    std::array<float, 3> coords;
};

class VertexBuffer
{
private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;

    unsigned int m_nbElements;

public:
    VertexBuffer();
    VertexBuffer(std::vector<Vertex> vertices, 
            std::vector<int> triangles, bool staticDraw=true);

    void Load(std::vector<Vertex> vertices, 
            std::vector<int> triangles, bool staticDraw=true);
    void Bind();
    void Unbind();
    void Destroy();
    void Draw();
};
