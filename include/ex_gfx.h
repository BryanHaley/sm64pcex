#ifndef EX_GFX_H
#define EX_GFX_H

#ifdef __cplusplus
extern "C" {
#endif

void ex_load_model(char* filename);
void ex_load_shader(char* vsFilename, char* fsFilename);
void ex_draw_model();

#ifdef __cplusplus
}
#endif

#endif