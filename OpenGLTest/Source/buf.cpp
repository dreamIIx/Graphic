#include "buf.hpp"

namespace dx
{

Buffer::Buffer() noexcept(false)
{
    id = ::std::make_shared<GLuint>();
    glGenBuffers(1, id.get());
}

Buffer::Buffer(const void* data, GLsizeiptr sz, GLenum bufferType, GLenum storageType) noexcept(false)
{
    id = ::std::make_shared<GLuint>();
    glGenBuffers(1, id.get());
    init(data, sz, bufferType, storageType);
}

Buffer::Buffer(const Buffer& instance) noexcept(true)
{
    *this = instance;
}

Buffer::Buffer(Buffer&& instance) noexcept(true)
{
    *this = ::std::move(instance);
}

Buffer::~Buffer() noexcept(false)
{
    if (id.use_count() == 1)
        glDeleteBuffers(1, id.get());
}

Buffer& Buffer::operator=(const Buffer& instance) noexcept(true)
{
    id = instance.id;
    return *this;
}

Buffer& Buffer::operator=(Buffer&& instance) noexcept(true)
{
    id = ::std::move(instance.id);
    return *this;
}

Buffer::operator GLuint() const noexcept(true)
{
    return *id.get();
}

Buffer::operator GLuint*() const noexcept(true)
{
    return id.get();
}

void Buffer::bind(GLenum bufferType) noexcept(false)
{
    glBindBuffer(bufferType, *id.get());
}

}