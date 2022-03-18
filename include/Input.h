#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

enum KeyValue
{
    KEY_F1,
    KEY_ESCAPE,
    KEY_COUNT
};

struct Key
{
    bool down;
    bool changed;
};

static Key keys[KEY_COUNT] = {};

class Input
{
public:
    static glm::vec2 mousePosition;

    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

    static void KeyCallback(GLFWwindow *window, int key,
            int scancode, int action, int mods);
    static void CursorCallback(GLFWwindow *window,
            double xpos, double ypos);
};
