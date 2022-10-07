#pragma once

namespace dx
{

void Buffer::init(const void* data, GLsizeiptr sz, GLenum bufferType, GLenum storageType) noexcept(false)
{
    glBindBuffer(bufferType, *id.get());
    glBufferData(bufferType, sz, data, storageType);
}

}