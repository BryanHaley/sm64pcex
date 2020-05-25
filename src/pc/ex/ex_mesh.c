#include "ex/ex_gfx.h"
#include "ex/ex_model.h"
#include "ex/ex_mesh.h"
#include "ex/ex_ogl.h"
#include "ex/cglm/cglm.h"
#include <stdlib.h>

ex_mesh_t* ex_create_mesh(size_t num_indices, GLuint* indices, size_t num_vertices, GLfloat* vertices, GLuint texture)
{
    //return NULL;
    if (num_vertices <= 0 || num_indices <= 0) return NULL;

    // create mesh to add to model
    ex_mesh_t* mesh = (ex_mesh_t*) calloc(1, sizeof(ex_mesh_t));

    // create VAO and bind it
    glGenVertexArrays(1, &(mesh->VAO));
    glBindVertexArray(mesh->VAO);

    glGenBuffers(1, &(mesh->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*((num_vertices*3)+(num_vertices*2)), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &(mesh->EBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*num_indices, indices, GL_STATIC_DRAW);

    mesh->EBO_len = num_indices;
    mesh->TexCoordOffset = (num_vertices*3)*sizeof(GLfloat);
    mesh->texture = texture;

    return mesh;
}

#define DEGREES(x) (x * 0x10000 / 360)

void ex_draw_mesh(ex_mesh_t* mesh)
{
    ex_use_shader(ex_mesh_shader);

    Mat4 ex_model_matrix = GLM_MAT4_IDENTITY;
    Mat4 ex_scaled_model_matrix = GLM_MAT4_IDENTITY;
    Vec3f mario_spawn_position = (Vec3f) {-1328.0f, 350.0f, 4500.0f};
    Vec3s rotate = (Vec3s) { DEGREES((s16) 270), DEGREES((s16) 270), DEGREES((s16) 0) };
    Vec3f model_scale = (Vec3f) {5.0f, 5.0f, 5.0f};

    // Place the triange where Mario spawns
    //mtxf_translate(ex_model_matrix, mario_spawn_position);
    mtxf_rotate_xyz_and_translate(ex_model_matrix, mario_spawn_position, rotate);
    mtxf_scale_vec3f(ex_scaled_model_matrix, ex_model_matrix, model_scale);

    // pass model, view, projection matrices to shader
    glUniformMatrix4fv(glGetUniformLocation( ex_mesh_shader->shaderProgram, "model" ), 1, GL_FALSE, (float *) ex_scaled_model_matrix);
    glUniformMatrix4fv(glGetUniformLocation( ex_mesh_shader->shaderProgram, "view" ), 1, GL_FALSE, (float *) ex_view_matrix);
    glUniformMatrix4fv(glGetUniformLocation( ex_mesh_shader->shaderProgram, "projection" ), 1, GL_FALSE, (float *) ex_projection_matrix);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glEnableVertexAttribArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    // Load and bind the texture
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, mesh->texture );
    glUniform1i(glGetUniformLocation( ex_mesh_shader->shaderProgram, "colorTexture" ), 0);

    glVertexAttribPointer(glGetAttribLocation(ex_mesh_shader->shaderProgram, "position"), 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(glGetAttribLocation(ex_mesh_shader->shaderProgram, "position"));
    glVertexAttribPointer(glGetAttribLocation(ex_mesh_shader->shaderProgram, "texcoord"), 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(mesh->TexCoordOffset));
    glEnableVertexAttribArray(glGetAttribLocation(ex_mesh_shader->shaderProgram, "texcoord"));

    //printf("%d\n", glGetAttribLocation(ex_mesh_shader->shaderProgram, "texcoord"));
    // Draw the triangle
    glDrawElements(GL_TRIANGLES, mesh->EBO_len, GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(mesh->VAO);
}