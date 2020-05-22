#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#include "ex/cglm/cglm.h"
#include "ex/cglm/struct.h"
#include "ex/ex_gfx.h"
#include "ex/ex_model.h"
#include "ex/ex_mesh.h"

#include <stdio.h>

ex_mesh_t* process_mesh(struct aiMesh *mesh, const struct aiScene *scene);
ex_mesh_t* process_node(struct aiNode *node, const struct aiScene *scene, ex_model_t* model, int* model_index);
void find_num_meshes(struct aiNode *node, const struct aiScene *scene, ex_model_t* model);

ex_model_t* ex_load_model(const char* filename)
{
    const struct aiScene* scene = aiImportFile(filename, aiProcess_Triangulate);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        fprintf(stderr, "ASSIMP IMPORT ERROR :: %s", aiGetErrorString());
        return NULL;
    }

    ex_model_t* model = (ex_model_t*) calloc(1, sizeof(ex_model_t));

    find_num_meshes(scene->mRootNode, scene, model);

    model->meshes = (ex_mesh_t**) calloc(model->num_meshes, sizeof(ex_mesh_t*));

    int model_index = 0;
    process_node(scene->mRootNode, scene, model, &model_index);

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

ex_mesh_t* process_node(struct aiNode *node, const struct aiScene *scene, ex_model_t* model, int* model_index)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        struct aiMesh *ai_mesh = scene->mMeshes[node->mMeshes[i]]; 
        ex_mesh_t* mesh = process_mesh(ai_mesh, scene);

        model->meshes[(*model_index)++] = mesh;
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene, model, model_index);
    }
}

ex_mesh_t* process_mesh(struct aiMesh *mesh, const struct aiScene *scene)
{
    int num_indices = 0;
    int num_vertices = mesh->mNumVertices;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        num_indices += mesh->mFaces[i].mNumIndices;
    }

    ex_vertex_t* vertices = (ex_vertex_t*) calloc(num_vertices, sizeof(ex_vertex_t));
    ex_vertex_normal_t* vertex_normals = (ex_vertex_normal_t*) calloc(num_vertices, sizeof(ex_vertex_normal_t));
    ex_vertex_color_t* vertex_colors = (ex_vertex_color_t*) calloc(num_vertices, sizeof(ex_vertex_color_t));
    ex_vertex_texcoord_t* vertex_texcoords = (ex_vertex_texcoord_t*) calloc(num_vertices, sizeof(ex_vertex_texcoord_t));
    GLuint* indices = (unsigned int*) calloc(num_indices, sizeof(GLuint));

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices[i].x = mesh->mVertices[i].x;
        vertices[i].y = mesh->mVertices[i].y;
        vertices[i].z = mesh->mVertices[i].z;
        vertex_normals[i].nx = mesh->mNormals[i].x;
        vertex_normals[i].ny = mesh->mNormals[i].y;
        vertex_normals[i].nz = mesh->mNormals[i].z;
        vertex_colors[i].color_r = 1.0f;
        vertex_colors[i].color_g = 1.0f;
        vertex_colors[i].color_b = 1.0f;
        //vertex_texcoords[i].u = mesh->mTextureCoords[i].u;
        //vertex_texcoords[i].v = mesh->mTextureCoords[i].v;
        vertex_texcoords[i].u = 0.0f;
        vertex_texcoords[i].v = 0.0f;
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

    return ex_create_mesh(num_vertices, vertices, vertex_normals, vertex_colors, vertex_texcoords, num_indices, indices);
}

void ex_draw_model(ex_model_t* model)
{
    for (int i = 0; i < model->num_meshes; i++)
    {
        ex_draw_mesh(model->meshes[i]);
    }
}