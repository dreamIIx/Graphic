#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "err_def.hpp"

namespace dx
{

class Window
{
private:
    bool _updateViewport;
    ::std::pair<int, int> winSize;
    GLFWwindow* _wnd;
    GLFWmonitor* monitor;
    const GLFWvidmode* mode;

public:
    Window() noexcept(true);
    Window(int win_width, int win_height, const char* winName) noexcept(false);
    ~Window() noexcept(false);

    operator GLFWwindow*() noexcept(true);

    static void framebuffer_size_callback(GLFWwindow* awnd, int width, int height) noexcept(false);
    static void CallbackResize(GLFWwindow* awnd, int cx, int cy) noexcept(false);

    void create(const char* winName) noexcept(false);
    bool isFullscreen() noexcept(false);
    void switchFullcreen() noexcept(false);
    inline bool is_closed() noexcept(false);

};

}

#include "window.ipp"