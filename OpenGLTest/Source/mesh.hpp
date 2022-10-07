#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "err_def.hpp"

#include "shader.hpp"
#include "tx.hpp"
#include "buf.hpp"
#include "va.hpp"

namespace dx
{

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
public:
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];

    Vertex() noexcept(true);

};

class Mesh
{
public:
    dx::VertexArray VAO;

private:
    dx::Buffer VBO;
    dx::Buffer EBO;

public:
    ::std::vector<Vertex>           vertices;
    ::std::vector<GLuint>           indices;
    ::std::vector<dx::Texture>      textures;

    Mesh(const ::std::vector<Vertex>& avertices, const ::std::vector<GLuint>& aindices, const ::std::vector<dx::Texture>& atextures) noexcept(false);
    //~Mesh() noexcept(false);

    void draw(dx::Shader& shader) noexcept(false);

private:
    void init() noexcept(false);

};

}