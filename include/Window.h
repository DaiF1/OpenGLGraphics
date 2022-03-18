#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static int WINDOW_OK = 0;

class Window
{
private:
    bool m_FullScreen = false;
    GLFWwindow *m_Window = nullptr;

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
};

static Window window;
