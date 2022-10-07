#include "va.hpp"

namespace dx
{

VertexArray::VertexArray()
{
    id = ::std::make_shared<GLuint>();
    glGenVertexArrays(1, id.get());
}

VertexArray::VertexArray(const VertexArray& instance) noexcept(true)
{
    *this = instance;
}

VertexArray::VertexArray(VertexArray&& instance) noexcept(true)
{
    id = ::std::move(instance.id);
}

VertexArray::~VertexArray() noexcept(false)
{
    if (id.use_count() == 1)
        glDeleteVertexArrays(1, id.get());
}

VertexArray& VertexArray::operator=(const VertexArray& instance) noexcept(true)
{
    id = instance.id;
    return *this;
}

VertexArray& VertexArray::operator=(VertexArray&& instance) noexcept(true)
{
    id = ::std::move(instance.id);
    return *this;
}

VertexArray::operator GLuint() const noexcept(true)
{
    return *id.get();
}

VertexArray::operator GLuint*() const noexcept(true)
{
    return id.get();
}

void VertexArray::bind() noexcept(false)
{
    glBindVertexArray(*id.get());
}

}