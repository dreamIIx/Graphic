#pragma once

#include <string>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "err_def.hpp"

#include "mesh.hpp"

namespace dx
{

unsigned int TextureFromFile(const char* path, const ::std::string& directory, bool gamma = false);

class Model 
{
public:
    bool gammaCorrection;
    ::std::string directory;
    ::std::vector<dx::Texture>  textures_loaded;
    ::std::vector<dx::Mesh>     meshes;

    Model(const ::std::string& dir, const ::std::string& path, bool gamma = false) noexcept(false);

    void draw(dx::Shader& shader) noexcept(false);
    
private:
    void loadModel(const ::std::string& dir, const ::std::string& path) noexcept(false);
    void processNode(aiNode* node, const aiScene* scene) noexcept(false);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene) noexcept(false);
    ::std::vector<dx::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, ::std::string typeName) noexcept(false);

};

}