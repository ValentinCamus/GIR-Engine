#include "ModelLoader.hpp"
#include <Engine/Manager/Manager.hpp>

namespace gir
{
    Model* ModelLoader::Load(const std::string& filepath)
    {
        Manager<Texture2D>::Clear();
        Manager<Material>::Clear();
        Manager<Mesh>::Clear();
        Manager<Model>::Clear();

        std::string name = filepath.substr(filepath.find_last_of('/') + 1);
        auto* model      = Manager<Model>::Add(name);

        // Read file via Assimp
        Assimp::Importer importer;
        unsigned int flags   = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
        const aiScene* scene = importer.ReadFile(filepath, flags);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Logger::Error("Assimp: {}", importer.GetErrorString());
            return nullptr;
        }

        ProcessAssimpNode(scene->mRootNode, scene, model);

        return model;
    }

    void ModelLoader::ProcessAssimpNode(aiNode* node, const aiScene* scene, Model* model)
    {
        // Process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            // The node object only contains indices to index the actual objects in the scene.
            // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            model->AddMesh(ProcessAssimpMesh(mesh, scene, model));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; ++i) { ProcessAssimpNode(node->mChildren[i], scene, model); }
    }

    Element ModelLoader::ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene, Model* model)
    {
        // Data to fill
        std::vector<unsigned> indices;
        std::vector<Mesh::Vertex> vertices;

        // Walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            // Positions
            Vec3f vertex;
            vertex.x = mesh->mVertices[i].x;
            vertex.y = mesh->mVertices[i].y;
            vertex.z = mesh->mVertices[i].z;

            // Normals
            Vec3f normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            // Texture coordinates
            Vec2f texCoord;
            if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
            {
                // A vertex can contain up to 8 different texture coordinates.
                // We thus make the assumption that we won't use models where a vertex
                // can have multiple texture coordinates so we always take the first set (0).
                texCoord.x = mesh->mTextureCoords[0][i].x;
                texCoord.y = mesh->mTextureCoords[0][i].y;
            }
            else
                texCoord = {0.0f, 0.0f};

            // tangent
            Vec3f tangent;
            tangent.x = mesh->mTangents[i].x;
            tangent.y = mesh->mTangents[i].y;
            tangent.z = mesh->mTangents[i].z;

            // bi-tangent
            Vec3f bitangent;
            bitangent.x = mesh->mBitangents[i].x;
            bitangent.y = mesh->mBitangents[i].y;
            bitangent.z = mesh->mBitangents[i].z;

            vertices.push_back({vertex, normal, texCoord, tangent, bitangent});
        }

        // Now wak through each of the mesh's faces (a face is a mesh its triangle)
        // and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            // Retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; ++j) { indices.push_back(face.mIndices[j]); }
        }

        Material* material = LoadMaterial(mesh, scene, model);
        std::string name   = model->GetName() + "_Mesh" + std::to_string(model->MaterialCount());

        return {material, Manager<Mesh>::Add(name, vertices, indices)};
    }

    Material* ModelLoader::LoadMaterial(aiMesh* mesh, const aiScene* scene, Model* model)
    {
        std::string name  = model->GetName() + "_Mat" + std::to_string(model->MaterialCount());
        auto* material    = Manager<Material>::Add(name);
        aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

        // 1. normal maps
        std::vector<Texture2D*> normalMaps = LoadMaterialTextures(aiMat, aiTextureType_HEIGHT);
        // 2. albedo maps
        std::vector<Texture2D*> albedoMaps = LoadMaterialTextures(aiMat, aiTextureType_DIFFUSE);
        // 3. metalness maps
        std::vector<Texture2D*> metalnessMaps = LoadMaterialTextures(aiMat, aiTextureType_AMBIENT);
        // 4. roughness maps
        std::vector<Texture2D*> roughnessMaps = LoadMaterialTextures(aiMat, aiTextureType_SHININESS);
        // 5. alpha maps
        std::vector<Texture2D*> alphaMaps = LoadMaterialTextures(aiMat, aiTextureType_OPACITY);

        if (!normalMaps.empty()) material->SetAttribute(Material::EAttribute::NORMAL, normalMaps[0]);

        if (!albedoMaps.empty())
            material->SetAttribute(Material::EAttribute::ALBEDO, albedoMaps[0]);
        else
        {
            aiColor3D color;
            aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, color);

            Vec4f albedo(color.r, color.g, color.b, 1.f);
            material->SetAttribute(Material::EAttribute::ALBEDO, albedo);
        }

        if (!metalnessMaps.empty())
            material->SetAttribute(Material::EAttribute::METALNESS, metalnessMaps[0]);
        else
        {
            int metalness;
            aiMat->Get(AI_MATKEY_COLOR_AMBIENT, metalness);

            material->SetAttribute(Material::EAttribute::ALBEDO, Vec4f(metalness));
        }

        if (!roughnessMaps.empty())
            material->SetAttribute(Material::EAttribute::ROUGHNESS, roughnessMaps[0]);
        else
        {
            int roughness;
            aiMat->Get(AI_MATKEY_SHININESS, roughness);

            material->SetAttribute(Material::EAttribute::ALBEDO, Vec4f(roughness));
        }

        if (!alphaMaps.empty())
            material->SetAttribute(Material::EAttribute::ALPHA, roughnessMaps[0]);
        else
        {
            float alpha;
            aiMat->Get(AI_MATKEY_OPACITY, alpha);

            material->SetAttribute(Material::EAttribute::ALPHA, Vec4f(alpha));
        }

        return material;
    }

    // Checks all material textures of a given type and loads the textures if they're not loaded yet.
    std::vector<Texture2D*> ModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
    {
        std::vector<Texture2D*> textures;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString filepath;
            mat->GetTexture(type, i, &filepath);

            // TODO: check if filepath was loaded before
            textures.push_back(TextureLoader::Load(FileSystem::GetAssetsDir() + filepath.C_Str()));
        }
        return textures;
    }
} // namespace gir