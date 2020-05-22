#include "ex/ex_gfx.h"
#include "ex/ex_ogl.h"

void ex_change_context(bool use_ex_pc_context)
{
    SDL_GL_MakeCurrent(ex_window, use_ex_pc_context ? ex_pc_context : ex_n64_context);
}