#include "Window.h"
#include "Input.h"
#include <GLFW/glfw3.h>

int Window::m_width = 1280;
int Window::m_height = 720;

Window::Window()
{

}

Window::~Window()
{

}

int Window::Create()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "[Error]: Failed to initialize GLFW." << '\n';
        return -1;
    }

    // Window settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int windowWidth = 1280;
    const int windowHeight = 720;
    const char *windowTitle = "OpenGL";

    // Window Creation
    m_Window = glfwCreateWindow(
            windowWidth,
            windowHeight,
            windowTitle,
            nullptr,
            nullptr
    );

    if (!m_Window)
    {
        std::cout << "[Error]: Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(m_Window, Input::KeyCallback);
    glfwSetCursorPosCallback(m_Window, Input::CursorCallback);
    glfwSetWindowSizeCallback(m_Window, Window::WindowCallback);

    glfwMakeContextCurrent(m_Window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        std::cout << "[Error]: Failed to initialize GLEW" << std::endl;
    
    glViewport(0, 0, 1280, 720);
    return 0;
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_Window, GL_TRUE);
}

void Window::Destroy()
{
    glfwTerminate();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_Window);
}

void Window::Loop()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
    
    // Clear the screen
    glClearColor(0.266f, 0.466f, 0.698f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::IsFullScreen()
{
    return glfwGetWindowMonitor(m_Window) != nullptr;
}

void Window::SetFullScreen(bool full)
{
    if (!full)
    {
        glfwSetWindowMonitor(m_Window, nullptr,
            100, 100, 1280, 720, GL_DONT_CARE);
        return;
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwSetWindowMonitor(m_Window, monitor,
            0, 0, mode->width, mode->height, GL_DONT_CARE);
}

void Window::WindowCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}

glm::vec2 Window::GetScreenResolution() const
{
    glm::vec2 result(m_width, m_height);
    return result;
}
