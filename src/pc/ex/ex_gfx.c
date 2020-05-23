#include "ex/ex_gfx.h"

SDL_Window *ex_window;
SDL_GLContext ex_n64_context;
SDL_GLContext ex_pc_context;

GLuint ex_prev_shader_program = 0;
ex_shader_t *ex_mesh_shader = NULL, *ex_n64_frame_shader = NULL;
mat4 ex_model_mat4 = GLM_MAT4_IDENTITY_INIT, ex_view_mat4 = GLM_MAT4_IDENTITY_INIT, ex_perspective_mat4 = GLM_MAT4_IDENTITY_INIT;