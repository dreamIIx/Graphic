#include "model.hpp"

namespace dx
{

Model::Model(const ::std::string& dir, const ::std::string& path, bool gamma) noexcept(false) : gammaCorrection(gamma)
{
    loadModel(dir, path);
}

void Model::draw(dx::Shader& shader) noexcept(false)
{
    shader.use();
    for(size_t i {0}; i < meshes.size(); ++i)
    {
        meshes[i].draw(shader);
    }
}

void Model::loadModel(const ::std::string& dir, const ::std::string& path) noexcept(false)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    ER_IF(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode,
        ::std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << ::std::endl;,
            return;)
    directory = dir;
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) noexcept(false)
{
    for(size_t i {0}; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(size_t i {0}; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) noexcept(false)
{
    ::std::vector<Vertex> vertices;
    ::std::vector<GLuint> indices;
    ::std::vector<dx::Texture> textures;

    for(unsigned int i = 0u; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        glm::vec3 vector(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Position = vector;
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.f, 0.f);
        }

        vertices.push_back(vertex);
    }
    for(unsigned int i = 0u; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0u; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);        
    }
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    ::std::vector<dx::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "tx_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    ::std::vector<dx::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "tx_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    ::std::vector<dx::Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "tx_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    /*::std::vector<dx::Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());*/
    
    return Mesh(vertices, indices, textures);
}

::std::vector<dx::Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, ::std::string typeName) noexcept(false)
{
    auto tx_foo = []()
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        };
    ::std::vector<dx::Texture> textures;
    for(unsigned i = 0u; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        ::std::string path = directory.c_str();
        path += "/";
        mat->GetTexture(type, i, &str);
        path += str.C_Str();
        bool skip = false;
        for(size_t j {0}; j < textures_loaded.size(); ++j)
        {
            if (std::strcmp(textures_loaded[j].path.data(), path.c_str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            dx::Texture texture(GL_TEXTURE_2D);
            texture.loadImage(path.c_str(), GL_TEXTURE_2D, tx_foo);
            texture.type = typeName;
            texture.path = path;
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

}