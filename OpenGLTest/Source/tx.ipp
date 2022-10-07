#pragma once

namespace dx
{

void Texture::loadImage(const char* filename, GLenum dimtype, auto& post_foo) noexcept(false)
{
    bind(dimtype);
    ::cv::Mat data = ::cv::imread(filename);
    ER_IFN(data.data,
        std::cerr << "[ERR] Failed to load texture" << std::endl;,
            )
    else
    {
        GLenum format = GL_RGB;
        if (data.channels() == 1)
        {
            format = GL_RED;
        }
        else if (data.channels() == 3)
        {
            format = GL_RGB;
        }
        else if (data.channels() == 4)
        {
            format = GL_RGBA;
        }

        glTexImage2D(dimtype, 0, format, data.cols, data.rows, 0, format, GL_UNSIGNED_BYTE, data.data);
        glGenerateMipmap(dimtype);
        post_foo();
    }
}

}