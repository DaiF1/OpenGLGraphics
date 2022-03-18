#include "Input.h"
#include <glm/fwd.hpp>
#include <iostream>

glm::vec2 Input::mousePosition = glm::vec2();

bool Input::IsKeyPressed(int key)
{
    bool pressed = keys[key].down && keys[key].changed;
    keys[key].changed = false;
    return pressed;
}

bool Input::IsKeyReleased(int key)
{
    bool released = !keys[key].down && keys[key].changed;
    keys[key].changed = false;
    return released;
}

void Input::KeyCallback(GLFWwindow *window, int key,
        int scancode, int action, int mods)
{
    switch (key)
    {
        case GLFW_KEY_F1:
        {
            bool down = action == GLFW_PRESS;
            keys[KEY_F1].changed = 
                down != keys[KEY_F1].down 
                && action != GLFW_REPEAT;
            keys[KEY_F1].down = down;
        } break;

        case GLFW_KEY_ESCAPE:
        {
            bool down = action == GLFW_PRESS;
            keys[KEY_ESCAPE].changed = 
                down != keys[KEY_ESCAPE].down 
                && action != GLFW_REPEAT;
            keys[KEY_ESCAPE].down = down;
        } break;
    }
}

void Input::CursorCallback(GLFWwindow *window, 
        double xpos, double ypos)
{
    mousePosition.x = xpos;
    mousePosition.y = ypos;
}
