#pragma once

#include <memory>

#include <glad/glad.h>

#include "err_def.hpp"

namespace dx
{

class VertexArray
{
public:
    ::std::shared_ptr<GLuint> id;

    VertexArray() noexcept(false);
    VertexArray(const VertexArray& instance) noexcept(true);
    VertexArray(VertexArray&& instance) noexcept(true);
    ~VertexArray() noexcept(false);

    VertexArray& operator=(const VertexArray& instance) noexcept(true);
    VertexArray& operator=(VertexArray&& instance) noexcept(true);
    operator GLuint() const noexcept(true);
    operator GLuint*() const noexcept(true);

    void bind() noexcept(false);

};

}