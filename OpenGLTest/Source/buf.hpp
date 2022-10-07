#pragma once

#include <memory>

#include <glad/glad.h>

#include "err_def.hpp"

namespace dx
{

class Buffer
{
public:
    std::shared_ptr<GLuint> id;

    Buffer() noexcept(false);
    Buffer(const void* data, GLsizeiptr sz, GLenum bufferType, GLenum storageType) noexcept(false);
    Buffer(const Buffer& instance) noexcept(true);
    Buffer(Buffer&& instance) noexcept(true);
    ~Buffer() noexcept(false);

    Buffer& operator=(const Buffer& instance) noexcept(true);
    Buffer& operator=(Buffer&& instance) noexcept(true);
    operator GLuint() const noexcept(true);
    operator GLuint*() const noexcept(true);

    void bind(GLenum bufferType) noexcept(false);
    inline void init(const void* data, GLsizeiptr sz, GLenum bufferType, GLenum storageType) noexcept(false);

};

}

#include "buf.ipp"