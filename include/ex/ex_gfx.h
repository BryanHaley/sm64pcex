#ifndef EX_GFX_H
#define EX_GFX_H

#include "ex/ex_model.h"
#include "ex/ex_ogl.h"
#include "ex/ex_shader.h"

extern SDL_Window *ex_window;
extern SDL_GLContext ex_n64_context;
extern SDL_GLContext ex_pc_context;

extern GLuint ex_prev_shader_program;
extern ex_shader_t* ex_mesh_shader;
extern mat4 model, view, perspective;

void ex_change_context(bool use_ex_pc_context);

void ex_init_shader();
void ex_use_shader();
void ex_restore_prev_shader();

ex_model_t* ex_load_model(const char* filename);
void ex_draw_model(ex_model_t* model);

#endif