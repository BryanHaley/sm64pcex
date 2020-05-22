#include "ex/ex_gfx.h"
#include "ex/ex_model.h"
#include "ex/ex_mesh.h"
#include "ex/ex_ogl.h"
#include "ex/cglm/cglm.h"
#include <stdlib.h>

ex_mesh_t* ex_create_mesh(size_t num_vertices, ex_vertex_t* vertices, ex_vertex_normal_t* vertex_normals, ex_vertex_color_t* vertex_colors, ex_vertex_texcoord_t* vertex_texcoords, size_t num_indices, GLuint* indices)
{
    //return NULL;
    if (num_vertices <= 0 || num_indices <= 0) return NULL;

    // create mesh to add to model
    ex_mesh_t* mesh = (ex_mesh_t*) calloc(1, sizeof(ex_mesh_t));

    // attributes
    //attribute vec4 position;
    //attribute vec3 normal;
    //attribute vec3 color;
    //attribute vec2 texture;

    // create VAO and bind it
    glGenVertexArrays(1, &(mesh->VAO));
    glBindVertexArray(mesh->VAO);

    // create element buffer and bind it
    glGenBuffers(1, &(mesh->EBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);

    // load indices into buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * num_indices, indices, GL_STATIC_DRAW);
    mesh->EBO_len = num_indices;

    // create vertex buffer, bind it, load the data into it, and point the attribute to the buffer
    glGenBuffers(1, &(mesh->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ex_vertex_t)*num_vertices, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(ex_mesh_shader->attributePosition);
    glVertexAttribPointer(ex_mesh_shader->attributePosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    mesh->VBO_len = num_vertices;

    // vertex normals
    /*glGenBuffers(1, &(mesh->VNBO));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VNBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ex_vertex_normal_t)*num_vertices, vertex_normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(ex_mesh_shader->attributeNormal);
    glVertexAttribPointer(ex_mesh_shader->attributeNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // vertex colors
    glGenBuffers(1, &(mesh->VCBO));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VCBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ex_vertex_color_t)*num_vertices, vertex_colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(ex_mesh_shader->attributeColor);
    glVertexAttribPointer(ex_mesh_shader->attributeColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // tex coords
    glGenBuffers(1, &(mesh->VTBO));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VTBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ex_vertex_texcoord_t)*num_vertices, vertex_texcoords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(ex_mesh_shader->attributeTexture);
    glVertexAttribPointer(ex_mesh_shader->attributeTexture, 2, GL_FLOAT, GL_FALSE, 0, 0);*/

    return mesh;
}

void ex_draw_mesh(ex_mesh_t* mesh)
{
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    mat4 perspective = GLM_MAT4_IDENTITY_INIT;
    mat4 mvp = GLM_MAT4_IDENTITY_INIT;

    glm_perspective_default(320.0f/240.0f,perspective);
    vec3 model_translate = GLM_VEC3_ZERO_INIT;
    model_translate[2] = -3.0f;
    glm_translate(model, model_translate);

    glm_mat4_mul(model, view, mvp);
    glm_mat4_mul(mvp, perspective, mvp);

    /*fprintf(stderr, "MVP Matrix Row 0: [%f][%f][%f][%f]\n", mvp[0][0], mvp[0][1], mvp[0][2], mvp[0][3]);
    fprintf(stderr, "MVP Matrix Row 1: [%f][%f][%f][%f]\n", mvp[1][0], mvp[1][1], mvp[1][2], mvp[1][3]);
    fprintf(stderr, "MVP Matrix Row 2: [%f][%f][%f][%f]\n", mvp[2][0], mvp[2][1], mvp[2][2], mvp[2][3]);
    fprintf(stderr, "MVP Matrix Row 3: [%f][%f][%f][%f]\n", mvp[3][0], mvp[3][1], mvp[3][2], mvp[3][3]);
    fprintf(stderr, "-----------------------------------\n");*/

    glUniformMatrix4fv(ex_mesh_shader->uniformView, 1, GL_FALSE, (float *)mvp);
    glDrawElements(GL_TRIANGLES, mesh->EBO_len, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);

    /*glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->EBO_len, mesh->EBO_buf, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh->VBO_len, mesh->VBO_buf, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES,mesh->num_faces,GL_UNSIGNED_INT,0);*/
}