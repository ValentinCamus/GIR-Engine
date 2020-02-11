#include "ModelLoader.hpp"

namespace gir
{
    Model* ModelLoader::Load(const std::string &filepath)
    {
        std::string directory = filepath.substr(0, filepath.find_last_of('/'));

        Logger::Debug(directory);
        auto* model = new Model(directory);

        // Read file via Assimp
        Assimp::Importer importer;
        unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
        const aiScene* scene = importer.ReadFile(filepath, flags);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Logger::Error("Assimp: {}", importer.GetErrorString());
            return nullptr;
        }

        ProcessAssimpNode(scene->mRootNode, scene, model);

        return model;
    }

    void ModelLoader::ProcessAssimpNode(aiNode *node, const aiScene *scene, Model* model)
    {
        // Process each mesh located at the current node
        for(unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            // The node object only contains indices to index the actual objects in the scene.
            // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            model->AddElement(ProcessAssimpMesh(mesh, scene, model));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for(unsigned int i = 0; i < node->mNumChildren; ++i)
        {
            ProcessAssimpNode(node->mChildren[i], scene, model);
        }
    }

    Model::Element ModelLoader::ProcessAssimpMesh(aiMesh *mesh, const aiScene *scene, Model* model)
    {
        // Data to fill
        Mesh::Vertices vertices;
        std::vector<unsigned> indices;

        // Walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            Vec3f vertex;
            Vec3f normal;
            Vec2f texCoord;
            Vec3f tangent;
            Vec3f biTangent;

            // Positions
            vertex.x = mesh->mVertices[i].x;
            vertex.y = mesh->mVertices[i].y;
            vertex.z = mesh->mVertices[i].z;
            vertices.vertices.push_back(vertex);

            // Normals
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
            vertices.normals.push_back(normal);

            // Texture coordinates
            if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
            {
                // A vertex can contain up to 8 different texture coordinates.
                // We thus make the assumption that we won't use models where a vertex
                // can have multiple texture coordinates so we always take the first set (0).
                texCoord.x = mesh->mTextureCoords[0][i].x;
                texCoord.y = mesh->mTextureCoords[0][i].y;
            }
            else texCoord = {0.0f, 0.0f};
            vertices.textureCoordinates.push_back(texCoord);

            // tangent
            tangent.x = mesh->mTangents[i].x;
            tangent.y = mesh->mTangents[i].y;
            tangent.z = mesh->mTangents[i].z;
            vertices.tangents.push_back(tangent);

            // bi-tangent
            biTangent.x = mesh->mBitangents[i].x;
            biTangent.y = mesh->mBitangents[i].y;
            biTangent.z = mesh->mBitangents[i].z;
            vertices.biTangents.push_back(biTangent);
        }
        // Now wak through each of the mesh's faces (a face is a mesh its triangle)
        // and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; ++j) indices.push_back(face.mIndices[j]);
        }

        Material* material = LoadMaterial(mesh, scene, model);
        std::string name = model->GetName() + "_Mesh" + std::to_string(model->GetElements().size());

        return {Mesh(name, vertices, indices), material };
    }

    Material *ModelLoader::LoadMaterial(aiMesh *mesh, const aiScene *scene, Model* model)
    {
        std::string name = model->GetName() + "_Mat" + std::to_string(model->GetElements().size());
        auto* material = new Material(name);
        aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

        // 1. diffuse maps
        std::vector<Texture2D*> diffuseMaps = LoadMaterialTextures(aiMat, aiTextureType_DIFFUSE);
        // 2. specular maps
        std::vector<Texture2D*> specularMaps = LoadMaterialTextures(aiMat, aiTextureType_SPECULAR);
        // 3. normal maps
        std::vector<Texture2D*> normalMaps = LoadMaterialTextures(aiMat, aiTextureType_HEIGHT);

        if (!diffuseMaps.empty()) material->SetAttribute(Material::EAttribute::Diffuse, diffuseMaps[0]);
        if (!specularMaps.empty()) material->SetAttribute(Material::EAttribute::Specular, specularMaps[0]);
        if (!normalMaps.empty()) material->SetAttribute(Material::EAttribute::Normal, normalMaps[0]);

        return material;
    }

    // Checks all material textures of a given type and loads the textures if they're not loaded yet.
    std::vector<Texture2D*> ModelLoader::LoadMaterialTextures(aiMaterial *mat, aiTextureType type)
    {
        std::vector<Texture2D*> textures;

        for(unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString filepath;
            mat->GetTexture(type, i, &filepath);
            Logger::Debug(filepath.C_Str());

            // TODO: check if filepath was loaded before
            textures.push_back(TextureLoader::Load(FileSystem::GetAssetsDir()  + "/" + filepath.C_Str()));
        }
        return textures;
    }
}