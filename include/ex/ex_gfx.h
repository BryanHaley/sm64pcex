#ifndef EX_GFX_H
#define EX_GFX_H

#include "ex/ex_model.h"
#include "ex/ex_ogl.h"
#include "ex/ex_shader.h"
#include "ex/cglm/cglm.h"

extern SDL_Window *ex_window;
extern SDL_GLContext ex_n64_context;
extern SDL_GLContext ex_pc_context;

extern ex_shader_t* ex_mesh_shader;
extern ex_shader_t* ex_n64_frame_shader;
extern mat4 ex_model_mat4, ex_view_mat4, ex_perspective_mat4;

void ex_change_context(bool use_ex_pc_context);

void ex_init_gfx();
void ex_init_mesh_shader();
void ex_init_n64_frame_shader();
mat4* ex_camera_init();
void ex_use_shader(ex_shader_t* shader);
void ex_restore_prev_shader();

ex_model_t* ex_load_model(const char* filename);
void ex_draw_model(ex_model_t* model);

#endif