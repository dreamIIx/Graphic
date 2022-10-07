#include "tx.hpp"

namespace dx
{

Texture::Texture(GLenum dimtype) : id(::std::make_shared<GLuint>()), type(), path()
{
    glGenTextures(1, id.get());
}

Texture::Texture(const Texture& instance) noexcept(true)
{
    *this = instance;
}

Texture::Texture(Texture&& instance) noexcept(true)
{
    *this = ::std::move(instance);
}

Texture::~Texture() noexcept(false)
{
    if (id.use_count() == 1)
        glDeleteTextures(1, id.get());
}

Texture& Texture::operator=(const Texture& instance) noexcept(true)
{
    id = instance.id;
    type = instance.type;
    path = instance.path;
    return *this;
}

Texture& Texture::operator=(Texture&& instance) noexcept(true)
{
    id = ::std::move(instance.id);
    type = ::std::move(instance.type);
    path = ::std::move(instance.path);
    return *this;
}

Texture::operator GLuint() const noexcept(true)
{
    return *id.get();
}

Texture::operator GLuint*() const noexcept(true)
{
    return id.get();
}

void Texture::bind(GLenum dimtype) noexcept(false)
{
    glBindTexture(dimtype, *id.get());
}

}