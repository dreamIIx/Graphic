#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>

#include "err_def.hpp"

namespace dx
{

class Texture
{
public:
    ::std::shared_ptr<GLuint> id;
    ::std::string type;
    ::std::string path;

    Texture() noexcept(true);
    Texture(const Texture& instance) noexcept(true);
    Texture(Texture&& instance) noexcept(true);
    Texture(GLenum dimtype) noexcept(false);
    ~Texture() noexcept(false);

    Texture& operator=(const Texture& instance) noexcept(true);
    Texture& operator=(Texture&& instance) noexcept(true);
    operator GLuint() const noexcept(true);
    operator GLuint*() const noexcept(true);

    void bind(GLenum dimtype) noexcept(false);
    static void activate(GLenum txNum) noexcept(false)
    {
        glActiveTexture(txNum);
    }

    void loadImage(const char* filename, GLenum dimtype, auto& post_foo) noexcept(false);

};

}

#include "tx.ipp"