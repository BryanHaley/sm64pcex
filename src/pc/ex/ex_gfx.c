#include "ex/ex_gfx.h"

SDL_Window *ex_window;
SDL_GLContext ex_n64_context;
SDL_GLContext ex_pc_context;

GLuint ex_prev_shader_program = 0;
ex_shader_t *ex_mesh_shader = NULL, *ex_n64_frame_shader = NULL;
Mtx *ex_projection_matrix, *ex_view_matrix;