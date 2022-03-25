#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>>

#include <iostream>

static int WINDOW_OK = 0;

class Window
{
private:
    bool m_FullScreen = false;
    GLFWwindow *m_Window = nullptr;

    static int m_width, m_height;

    static void WindowCallback(GLFWwindow *window, int width, int height);

public:
    // Constructor
    Window();
    ~Window();

    int Create();
    void Close();
    void Destroy();

    bool ShouldClose();
    void Loop();

    bool IsFullScreen();
    void SetFullScreen(bool full);

    glm::vec2 GetScreenResolution() const;
};

static Window window;
