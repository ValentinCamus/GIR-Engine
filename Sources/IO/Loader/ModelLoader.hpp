#pragma once

#include <Core/Core.hpp>

#include <Engine/Mesh/Mesh.hpp>
#include <Engine/Mesh/Model.hpp>
#include <Engine/Mesh/VertexArrayObject.hpp>

#include <IO/Loader/TextureLoader.hpp>
#include <IO/FileSystem/FileSystem.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace gir
{
    class ModelLoader
    {
    public:
        static Model* Load(const std::string& filepath);

    private:
        static void ProcessAssimpNode(aiNode *node, const aiScene *scene, Model* model);

        static Element ProcessAssimpMesh(aiMesh *aiMesh, const aiScene *scene, Model* model);

        static Material* LoadMaterial(aiMesh *mesh, const aiScene *scene, Model* model);

        static std::vector<Texture2D*> LoadMaterialTextures(aiMaterial *mat, aiTextureType type);
    };
}



