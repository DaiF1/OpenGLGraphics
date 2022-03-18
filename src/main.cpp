#include "Window.h"
#include "Input.h"
#include "VertexBuffer.h"
#include "Shader.h"

#include <iostream>

#define GLEW_STATIC

static Shader shader;

static std::vector<Vertex> squareVertices = {
	//      Color                         Position
	Vertex{{0.9f,  0.1f, 0.12f, 1.0f},   {-0.5f, -0.5f, 0.0f}},
	Vertex{{0.1f,  0.9f, 0.12f, 1.0f},   {-0.5f,  0.5f, 0.0f}},
	Vertex{{0.12f, 0.9f, 0.1f,  1.0f},   { 0.5f,  0.5f, 0.0f}},
	Vertex{{0.12f, 0.1f, 0.9f,  1.0f},   { 0.5f, -0.5f, 0.0f}}
};

static std::vector<int> squareElements = {
    0, 1, 2,
    0, 2, 3
};

static std::vector<Vertex> starVertices = {
	//      Color                         Position
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   {  -0.4f,  0.125f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   {-0.125f,  0.125f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   {   0.0f,    0.5f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   { 0.125f,  0.125f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   {   0.4f,  0.125f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   {  0.13f, -0.125f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   {  0.29f,   -0.6f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   {   0.0f,  -0.29f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   { -0.29f,   -0.6f, 0.0f}},
	Vertex{{0.98f, 0.72f, 0.01f, 1.0f},   { -0.13f, -0.125f, 0.0f}}
};

static std::vector<int> starElements = {
	0, 1, 9,   1, 2, 3,
	3, 4, 5,   5, 6, 7,
	7, 8, 9,   9, 5, 7,
	9, 1, 3,   9, 3, 5
};

int main(int argc, char **argv)
{
    Window window = {};
    if (window.Create() != WINDOW_OK)
        return -1;

    shader.compile();
    glViewport(0, 0, 1280, 720);
    shader.bind();

    VertexBuffer vb(starVertices, starElements);

    // Main Loop
    while (!window.ShouldClose())
    {
        window.Loop();

        if (Input::IsKeyPressed(KEY_F1))
        {
            bool fullScreen = window.IsFullScreen();
            window.SetFullScreen(!fullScreen);
        }

        if (Input::IsKeyPressed(KEY_ESCAPE))
            window.Close(); 

        vb.Bind();
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    }

    vb.Destroy();
    window.Destroy();
}
