#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);

class Model{
public:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;

    Model(std::string const &path, bool gamma);

    void processNode(aiNode *node, const aiScene *scene);
    Mesh buildMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    
    void Draw(Shader &shader);
    void setModelMatrix(Shader& shader, const char* uniform);

    
};