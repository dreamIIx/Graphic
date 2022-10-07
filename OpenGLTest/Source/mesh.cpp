#include "mesh.hpp"

namespace dx
{

Vertex::Vertex() noexcept(true) :
    Position(0.f, 0.f, 0.f), Normal(0.f, 0.f, 0.f), TexCoords(0.f, 0.f),
    Tangent(0.f, 0.f, 0.f), Bitangent(0.f, 0.f, 0.f), m_BoneIDs({}), m_Weights({})
{

}

Mesh::Mesh(
    const ::std::vector<Vertex>& avertices,
    const ::std::vector<GLuint>& aindices,
    const ::std::vector<dx::Texture>& atextures) noexcept(false)
{
    VAO.bind();
    VBO.init(&avertices[0], avertices.size() * sizeof(Vertex), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    EBO.init(&aindices[0], aindices.size() * sizeof(GLuint), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    vertices = avertices;
    indices = aindices;
    textures = atextures;
    init();
}

/*Mesh::~Mesh() noexcept(false)
{

}*/

void Mesh::draw(dx::Shader& shader) noexcept(false)
{
    if (textures.size())
    {
        for(size_t i {0}; i < textures.size(); ++i)
        {
            dx::Texture::activate(GL_TEXTURE0 + i);

            ::std::string name = textures[i].type;
            if (name == "tx_diffuse")
            {
                //shader.setInt("material.diffuse", i);
                shader.setInt("texture1", i);
                
            }
            else if (name == "tx_specular")
            {
                shader.setInt("material.specular", i);
            }
            else if (name == "tx_normal")
            {

            }
            else
            {
                throw ::std::runtime_error("bad");
            }
        
            textures[i].bind(GL_TEXTURE_2D);
        }
        VAO.bind();
        VBO.bind(GL_ARRAY_BUFFER);
        EBO.bind(GL_ELEMENT_ARRAY_BUFFER);
        glDrawElements(GL_TRIANGLES, static_cast<GLuint>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        dx::Texture::activate(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::init() noexcept(false)
{
    VAO.bind();
    VBO.bind(GL_ARRAY_BUFFER);
    EBO.bind(GL_ELEMENT_ARRAY_BUFFER);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Tangent)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Bitangent)));
    glEnableVertexAttribArray(6);
    glVertexAttribIPointer(6, MAX_BONE_INFLUENCE, GL_INT, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_BoneIDs)));
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, MAX_BONE_INFLUENCE, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_Weights)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}