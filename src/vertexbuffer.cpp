#include <GL/glew.h>
#include <cstddef>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::vector<Vertex> vertices,
        std::vector<int> triangles,
        bool staticDraw)
{
    glCreateVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao); 

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*
            sizeof(Vertex), &vertices[0],
            (staticDraw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 
            sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
            sizeof(Vertex), (void*)offsetof(Vertex, coords));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(int)*triangles.size(), &triangles[0],
            (staticDraw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    m_nbElements = triangles.size();
}

void VertexBuffer::Bind()
{
    glBindVertexArray(m_vao);
}

void VertexBuffer::Unbind()
{
    glBindVertexArray(0);
}

void VertexBuffer::Destroy()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void VertexBuffer::Draw()
{
    Bind();
    glDrawElements(GL_TRIANGLES, m_nbElements, GL_UNSIGNED_INT, 0);
    Unbind();
}
