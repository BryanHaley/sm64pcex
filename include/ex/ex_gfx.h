#ifndef EX_GFX_H
#define EX_GFX_H

#include "ex/ex_model.h"
#include "ex/ex_ogl.h"
#include "ex/ex_shader.h"
#include "ex/cglm/cglm.h"
#include "engine/math_util.h"

#define N64_MAT4_TO_GLM_MAT4(n64_mat4, glm_mat4) {\
    glm_mat4[0][0] = n64_mat4[0][0]; glm_mat4[0][1] = n64_mat4[0][1]; glm_mat4[0][2] = n64_mat4[0][2]; glm_mat4[0][3] = n64_mat4[0][3];\
    glm_mat4[1][0] = n64_mat4[1][0]; glm_mat4[1][1] = n64_mat4[1][1]; glm_mat4[1][2] = n64_mat4[1][2]; glm_mat4[1][3] = n64_mat4[1][3];\
    glm_mat4[2][0] = n64_mat4[2][0]; glm_mat4[2][1] = n64_mat4[2][1]; glm_mat4[2][2] = n64_mat4[2][2]; glm_mat4[2][3] = n64_mat4[2][3];\
    glm_mat4[3][0] = n64_mat4[3][0]; glm_mat4[3][1] = n64_mat4[3][1]; glm_mat4[3][2] = n64_mat4[3][2]; glm_mat4[3][3] = n64_mat4[3][3]; }

extern SDL_Window *ex_window;
extern SDL_GLContext ex_n64_context;
extern SDL_GLContext ex_pc_context;

extern ex_shader_t* ex_mesh_shader;
extern ex_shader_t* ex_n64_frame_shader;
extern Mtx* ex_projection_matrix;
extern Mtx* ex_view_matrix;

void ex_change_context(bool use_ex_pc_context);

void ex_init_gfx();
void ex_init_mesh_shader();
void ex_init_n64_frame_shader();
mat4* ex_camera_init();
void ex_use_shader(ex_shader_t* shader);
void ex_restore_prev_shader();

ex_model_t* ex_load_model(const char* directory, const char* filename, const char* format);
void ex_draw_model(ex_model_t* model);

#endif