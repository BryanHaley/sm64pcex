#ifndef EX_SHADER_H
#define EX_SHADER_H

typedef struct
{
    GLuint shaderProgram;
    GLint attributePosition;
    GLint attributeNormal;
    GLint attributeColor;
    GLint attributeTexture;
    GLint uniformView;
    GLint uniformTexture0;
} ex_shader_t;

#endif