#ifndef EX_MESH_H
#define EX_MESH_H

#include "ex/cglm/cglm.h"
#include "ex_ogl.h"
#include <stdint.h>

typedef struct 
{
    GLuint VAO, EBO, VBO;
    size_t EBO_len, TexCoordOffset;
} ex_mesh_t;

ex_mesh_t* ex_create_mesh(size_t num_indices, GLuint* indices, size_t num_vertices, GLfloat* vertices);
void ex_draw_mesh(ex_mesh_t* mesh);

#endif