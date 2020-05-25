#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/material.h>
#include <assimp/postprocess.h>    // Post processing flags

#include "ex/cglm/cglm.h"
#include "ex/cglm/struct.h"
#include "ex/SOIL2/SOIL2.h"
#include "ex/ex_gfx.h"
#include "ex/ex_model.h"
#include "ex/ex_mesh.h"

#include <stdio.h>
#include <string.h>

ex_mesh_t* process_mesh(struct aiMesh *mesh, const char* directory, const struct aiScene *scene);
ex_mesh_t* process_node(struct aiNode *node, const char* directory, const struct aiScene *scene, ex_model_t* model, int* model_index);
void find_num_meshes(struct aiNode *node, const struct aiScene *scene, ex_model_t* model);

ex_model_t* ex_load_model(const char* directory, const char* filename, const char* format)
{
    char* fullpath = (char*) calloc(strlen(directory)+1+strlen(filename)+1+strlen(format)+1, sizeof(char));
    strcat(fullpath, directory);
    if (directory[strlen(directory)-1] != '/') strcat(fullpath, "/");
    strcat(fullpath, filename);
    strcat(fullpath, ".");
    strcat(fullpath, format);

    printf("Loading: %s\n", fullpath);

    const struct aiScene* scene = aiImportFile(fullpath, aiProcess_Triangulate);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        fprintf(stderr, "ASSIMP IMPORT ERROR :: %s\n", aiGetErrorString());
        return NULL;
    }

    ex_model_t* model = (ex_model_t*) calloc(1, sizeof(ex_model_t));

    find_num_meshes(scene->mRootNode, scene, model);

    model->meshes = (ex_mesh_t**) calloc(model->num_meshes, sizeof(ex_mesh_t*));

    int model_index = 0;

    char* tex_format = "png";
    char* tex_fullpath = (char*) calloc(strlen(directory)+1+strlen(filename)+1+strlen(tex_format)+1, sizeof(char));
    strcat(tex_fullpath, directory);
    if (directory[strlen(directory)-1] != '/') strcat(tex_fullpath, "/");
    strcat(tex_fullpath, filename);
    strcat(tex_fullpath, ".");
    strcat(tex_fullpath, tex_format);

    process_node(scene->mRootNode, tex_fullpath, scene, model, &model_index);

    free (fullpath);
    free (tex_fullpath);
    aiReleaseImport(scene);
    return model;
}

void find_num_meshes(struct aiNode *node, const struct aiScene *scene, ex_model_t* model)
{
    model->num_meshes += node->mNumMeshes;

    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        find_num_meshes(node->mChildren[i], scene, model);
    }
}

ex_mesh_t* process_node(struct aiNode *node, const char* directory, const struct aiScene *scene, ex_model_t* model, int* model_index)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        struct aiMesh *ai_mesh = scene->mMeshes[node->mMeshes[i]]; 
        ex_mesh_t* mesh = process_mesh(ai_mesh, directory, scene);

        model->meshes[(*model_index)++] = mesh;
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], directory, scene, model, model_index);
    }
}

ex_mesh_t* process_mesh(struct aiMesh *mesh, const char* directory, const struct aiScene *scene)
{
    int num_indices = 0;
    int num_vertices = mesh->mNumVertices;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        num_indices += mesh->mFaces[i].mNumIndices;
    }
    
    GLfloat* vertices = (GLfloat*) calloc((num_vertices*3)+(num_vertices*2), sizeof(GLfloat));
    GLuint* indices = (unsigned int*) calloc(num_indices, sizeof(GLuint));

    int last_index = 0;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices[i*3] = mesh->mVertices[i].x;
        vertices[i*3+1] = mesh->mVertices[i].y;
        vertices[i*3+2] = mesh->mVertices[i].z;
        last_index = i*3+3;
    }

    for(unsigned int i = 0; i < num_vertices; i++)
    {
        vertices[i*2+last_index] = mesh->mTextureCoords[0][i].x;
        vertices[i*2+1+last_index] = mesh->mTextureCoords[0][i].y;
    }

    int flCounter = 0;
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        struct aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices[flCounter++] = face.mIndices[j];
        }
    }

    GLuint texture = 0;

    if(mesh->mMaterialIndex >= 0)
    {
        /*
         * Blender doesn't support exporting texture names into model formats anymore! Fuck!
         */

        /*struct aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        struct aiString texturePath;
        if (aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, &texturePath, NULL, NULL, NULL, NULL, NULL, NULL) == aiReturn_SUCCESS)
        {
            // Had to use malloc here, was getting bogus characters otherwise
            char* fullpath = (char*) calloc(strlen(directory)+strlen(texturePath.data)+1, sizeof(char));
            strcat(fullpath, directory);
            strcat(fullpath, texturePath.data);

            printf("Loading: %s\n", fullpath);

            texture = SOIL_load_OGL_texture
            (
                fullpath,
                SOIL_LOAD_RGBA,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
            );
            free(fullpath);
        }
        else
        {
            fprintf(stderr, "ASSIMP IMPORT ERROR :: UNABLE TO LOAD TEXTURE %s\n", aiGetErrorString());
        }*/

        /*
         * For now just try to load "{modelname}.png" for the texture.
         */

        printf("Loading: %s\n", directory);

        texture = SOIL_load_OGL_texture
        (
            directory,
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS
        );

        if (texture < 0)
        {
            fprintf(stderr, "IMPORT ERROR :: UNABLE TO LOAD TEXTURE %s\n", directory);
        }
    }

    return ex_create_mesh(num_indices, indices, num_vertices, vertices, texture);
}

void ex_draw_model(ex_model_t* model)
{
    for (int i = 0; i < model->num_meshes; i++)
    {
        ex_draw_mesh(model->meshes[i]);
    }
}