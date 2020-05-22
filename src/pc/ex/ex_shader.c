#include "ex/ex_gfx.h"
#include "ex/ex_shader.h"
#include <stdlib.h>

GLuint ex_prev_shader_program = 0;
ex_shader_t* ex_mesh_shader = NULL;
mat4 model = GLM_MAT4_IDENTITY_INIT, view = GLM_MAT4_IDENTITY_INIT, perspective = GLM_MAT4_IDENTITY_INIT;

void checkCompileErrors(GLuint shader, char* type);

void ex_init_shader()
{
    ex_shader_t* shader = (ex_shader_t*) calloc(1, sizeof(ex_shader_t));
    ex_mesh_shader = shader;

    const GLchar* vShaderCode = "#version 120\n"
    //"uniform mat4 modelview;"
    "attribute vec3 position;"
    //"attribute vec3 normal;"
    //"attribute vec3 color;"
    //"attribute vec2 texture;"
    //"varying vec4 outcolor;"
    //"varying vec2 outtexture;"
    "void main() {"
    "gl_Position = vec4(position, 1.0);"
    //"vec4 light = vec4(-20,0,-40,0) * modelview;"
    //"vec3 lightDir = light.xyz;"
    //"float cosAngIncidence = dot(normalize(normal), normalize(lightDir));"
    //"cosAngIncidence = clamp(cosAngIncidence, 0, 1);"
    //"outcolor = vec4(color,1.0) * cosAngIncidence + vec4(0.1,0.1,0.1,1.0);"
    //"outcolor = vec4(color,1.0)"
    //"outtexture = texture; }";
    "}";

    const GLchar* fShaderCode = "#version 120\n"
    //"uniform sampler2D texture0;"
    //"varying vec4 outcolor;"
    //"varying vec2 outtexture;"
    "void main() {"
    //"vec4 color = texture2D(texture0,outtexture);"
    //"gl_FragColor = outcolor * color; }";
    "gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); }";

    // vertex shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader program
    shader->shaderProgram = glCreateProgram();
    glAttachShader(shader->shaderProgram, vertex);
    glAttachShader(shader->shaderProgram, fragment);
    glLinkProgram(shader->shaderProgram);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    ex_use_shader();

    shader->attributePosition = 0;
    shader->attributeNormal   = 2;
    shader->attributeColor    = 3;
    shader->attributeTexture  = 8;
    shader->uniformView = glGetUniformLocation( shader->shaderProgram, "modelview" );
    shader->uniformTexture0 = glGetUniformLocation( shader->shaderProgram, "texture0" );

    glBindAttribLocation(shader->shaderProgram, shader->attributePosition, "position");
    glBindAttribLocation(shader->shaderProgram, shader->attributeNormal, "normal");
    glBindAttribLocation(shader->shaderProgram, shader->attributeColor, "color");
    glBindAttribLocation(shader->shaderProgram, shader->attributeTexture, "texture");

    fprintf(stderr, "attributePosition: %d\nattributeNormal: %d\nattributeColor: %d\nattributeTexture: %d\nuniformView: %d\nuniformTexture0: %d\n",
            shader->attributePosition, shader->attributeNormal, shader->attributeColor, shader->attributeTexture, shader->uniformView, shader->uniformTexture0);

    ex_restore_prev_shader();
}

void ex_use_shader()
{
    glGetIntegerv(GL_CURRENT_PROGRAM,&ex_prev_shader_program);
    glUseProgram(ex_mesh_shader->shaderProgram);
}

void ex_restore_prev_shader()
{
    glUseProgram(ex_prev_shader_program);
}

void checkCompileErrors(GLuint shader, char* type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::PROGRAM_LINKIN_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
}