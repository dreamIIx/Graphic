#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "err_def.hpp"

namespace dx
{

class Shader
{
public:
    GLuint id;

    Shader(const ::std::string& vertexPath, const ::std::string& fragmentPath) noexcept(false);

    operator GLuint() noexcept(true);

    void use() noexcept(false);
    void setBool(const ::std::string& name, GLboolean value) const noexcept(false);
    void setInt(const ::std::string& name, GLint value) const noexcept(false);
    void setFloat(const std::string& name, GLfloat value) const noexcept(false);
};

}