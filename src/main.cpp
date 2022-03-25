#include "Window.h"
#include "Input.h"
#include "VertexBuffer.h"
#include "Shader.h"

#include <iostream>

#define GLEW_STATIC

static ShaderProgram shader;

glm::vec2 res(1280, 720);

static std::vector<Vertex> squareVertices = {
	//      Color                         Position
	Vertex{{0.9f,  0.1f, 0.12f, 1.0f},   {-1.f, -1.f, 1.0f}},
	Vertex{{0.1f,  0.9f, 0.12f, 1.0f},   {-1.f,  1.f, 1.0f}},
	Vertex{{0.12f, 0.9f, 0.1f,  1.0f},   { 1.f,  1.f, 0.0f}},
	Vertex{{0.12f, 0.1f, 0.9f,  1.0f},   { 1.f, -1.f, 0.0f}}
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

    shader.Load("./src/shaders/basic.vert", "./src/shaders/basic.frag");
    shader.Bind();
    VertexBuffer vb(squareVertices, squareElements);

    float dt = 0.0f;

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

        glm::vec2 pos(Input::mousePosition.x, res.y - Input::mousePosition.y);

        shader.PassFloat(dt, "u_time"); 
        shader.PassVec2(pos, "u_mouse");
        shader.PassVec2(res, "u_resolution");
        vb.Draw();

        dt += 0.016667;
    }

    shader.Destroy();
    vb.Destroy();
    window.Destroy();
}
