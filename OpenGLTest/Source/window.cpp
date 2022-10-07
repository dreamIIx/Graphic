#include "window.hpp"

namespace dx
{

Window::Window() noexcept(true)
    : _updateViewport(true), winSize(::std::make_pair(0, 0)), _wnd(nullptr), monitor(nullptr), mode(nullptr) {}

Window::Window(int win_width, int win_height, const char* winName) noexcept(false)
    : _updateViewport(true), winSize(::std::make_pair(win_width, win_height)), _wnd(nullptr), monitor(nullptr), mode(nullptr)
{
    create(winName);
}

Window::~Window() noexcept(false)
{
    glfwTerminate();
}

Window::operator GLFWwindow*() noexcept(true)
{
    return _wnd;
}

void Window::framebuffer_size_callback(GLFWwindow* awnd, int width, int height) noexcept(false)
{
    glViewport(0, 0, width, height);
}

void Window::CallbackResize(GLFWwindow* window, int cx, int cy) noexcept(false)
{

}

void Window::create(const char* winName) noexcept(false)
{
    _wnd = glfwCreateWindow(winSize.first, winSize.second, winName, NULL, NULL);
    ER_IF(_wnd == NULL,
        ::std::cerr << "[ERR] Failed to create GLFW _wnd" << ::std::endl;
        glfwTerminate();,
            return;)
    glfwMakeContextCurrent(_wnd);
    glfwSetWindowUserPointer(_wnd, this);
    glfwSetFramebufferSizeCallback(_wnd, Window::framebuffer_size_callback);

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
}

bool Window::isFullscreen() noexcept(false)
{
    return glfwGetWindowMonitor(_wnd) != NULL;
}

void Window::switchFullcreen() noexcept(false)
{
    if (isFullscreen())
    {
        glfwSetWindowMonitor(_wnd, NULL, 0, 0, winSize.first, winSize.second, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(_wnd, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
}

}