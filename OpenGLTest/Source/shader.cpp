#include "shader.hpp"

namespace dx
{

Shader::Shader(const ::std::string& vertexPath, const ::std::string& fragmentPath) noexcept(false)
{
    ::std::string vertexCode;
    ::std::string fragmentCode;
    ::std::ifstream vShaderFile(vertexPath);
    ::std::ifstream fShaderFile(fragmentPath);

    ER_IF(!vShaderFile.is_open() || !fShaderFile.is_open(),
        ::std::cerr << "[ERR] SHADER::FILE_NOT_SUCCESFULLY_READ" << ::std::endl;,
            )

    ::std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    ::std::cout << vShaderFile.rdbuf() << ::std::endl;
    ::std::cout << fShaderFile.rdbuf() << ::std::endl;
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLint success;
    static constexpr size_t szInfoLog = 1024ull;
    static constinit char infoLog[szInfoLog];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    ER_IFN(success,
        glGetShaderInfoLog(vertexShader, szInfoLog, NULL, infoLog);
        ::std::cerr << "[ERR] SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << ::std::endl;,
            )

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    ER_IFN(success,
        glGetShaderInfoLog(fragmentShader, szInfoLog, NULL, infoLog);
        ::std::cerr << "[ERR] SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << ::std::endl;,
            )

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    ER_IFN(success,
        glGetProgramInfoLog(id, szInfoLog, NULL, infoLog);,
            )

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::operator GLuint() noexcept(true)
{
    return id;
}

void Shader::use() noexcept(false)
{
    glUseProgram(id);
}

void Shader::setBool(const std::string& name, GLboolean value) const noexcept(false)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, GLint value) const noexcept(false)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, GLfloat value) const noexcept(false)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

}