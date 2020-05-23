#ifndef EX_MESH_H
#define EX_MESH_H

#include "ex/cglm/cglm.h"
#include "ex_ogl.h"
#include <stdint.h>

typedef struct 
{
    GLuint VBO, VNBO, VCBO, VTBO, EBO, VAO;
    size_t VBO_len, EBO_len;
} ex_mesh_t;

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} ex_vertex_t;

typedef struct
{
    GLfloat nx;
    GLfloat ny;
    GLfloat nz;
} ex_vertex_normal_t;

typedef struct
{
    GLfloat color_r;
    GLfloat color_g;
    GLfloat color_b;
} ex_vertex_color_t;

typedef struct
{
    GLfloat u;
    GLfloat v;
} ex_vertex_texcoord_t;

ex_mesh_t* ex_create_mesh(size_t num_vertices, ex_vertex_t* vertices, ex_vertex_normal_t* vertex_normals, ex_vertex_color_t* vertex_colors, ex_vertex_texcoord_t* vertex_texcoords, size_t num_indices, GLuint* indices);
void ex_draw_mesh(ex_mesh_t* mesh);

#endif