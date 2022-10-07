#pragma once

namespace dx
{

inline bool Window::is_closed() noexcept(false)
{
    return glfwWindowShouldClose(_wnd);
}

}