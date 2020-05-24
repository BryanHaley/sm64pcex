#include "ex/ex_gfx.h"
#include "ex/ex_shader.h"
#include <stdlib.h>

void checkCompileErrors(GLuint shader, char* type);

void ex_init_mesh_shader()
{
    ex_shader_t* shader = (ex_shader_t*) calloc(1, sizeof(ex_shader_t));
    ex_mesh_shader = shader;

    const GLchar* vShaderCode = "#version 120\n"
    "attribute vec3 position;\n"
    "attribute vec2 texcoord;\n"
    "uniform mat4 model;"
    "uniform mat4 view;"
    "uniform mat4 projection;"
    "varying vec2 outPos;\n"
    "void main() {\n"
    "gl_Position = projection * view * model * vec4(position, 1.0);"
    "outPos = texcoord; }";

    const GLchar* fShaderCode = "#version 120\n"
    "uniform sampler2D colorTexture;\n"
    "varying vec2 outPos;\n"
    "void main() {\n"
    //"gl_FragColor = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 1.0);\n"
    "gl_FragColor = texture2D(colorTexture, outPos);\n"
    //"gl_FragColor = vec4(outPos.xy, 0.0, 1.0);\n"
    "}";

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

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    shader->attributePosition = 0;
    shader->attributeNormal   = 2;
    shader->attributeColor    = 3;
    shader->attributeTexture  = 8;

    glBindAttribLocation(shader->shaderProgram, shader->attributePosition, "position");
    glBindAttribLocation(shader->shaderProgram, shader->attributeNormal, "normal");
    glBindAttribLocation(shader->shaderProgram, shader->attributeColor, "color");
    glBindAttribLocation(shader->shaderProgram, shader->attributeTexture, "texture");

    glLinkProgram(shader->shaderProgram);

    shader->uniformView = glGetUniformLocation( shader->shaderProgram, "modelview" );
    shader->uniformTexture0 = glGetUniformLocation( shader->shaderProgram, "colorTexture" );
    shader->uniformTexture1 = glGetUniformLocation( shader->shaderProgram, "depthTexture" );

    //fprintf(stderr, "attributePosition: %d\nattributeNormal: %d\nattributeColor: %d\nattributeTexture: %d\nuniformView: %d\nuniformTexture0: %d\nuniformTexture1: %d\n",
            //shader->attributePosition, shader->attributeNormal, shader->attributeColor, shader->attributeTexture, shader->uniformView, shader->uniformTexture0, shader->uniformTexture1);
}

void ex_init_n64_frame_shader()
{
    ex_shader_t* shader = (ex_shader_t*) calloc(1, sizeof(ex_shader_t));
    ex_n64_frame_shader = shader;

    const GLchar* vShaderCode = "#version 120\n"
    "attribute vec3 position;\n"
    "varying vec2 outPos;\n"
    "void main() {\n"
    "gl_Position = vec4(position, 1.0);\n"
    "outPos = vec2(position.x*0.5-0.5, position.y*0.5-0.5); }";

    const GLchar* fShaderCode = "#version 120\n"
    "uniform sampler2D colorTexture;\n"
    "uniform sampler2D depthTexture;\n"
    "varying vec2 outPos;\n"

    "void main() {\n"
    "gl_FragDepth = texture2D(depthTexture, outPos).r;\n"
    "gl_FragColor = texture2D(colorTexture, outPos);\n"
    "}";

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

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    shader->attributePosition = 0;
    shader->attributeNormal   = 2;
    shader->attributeColor    = 3;
    shader->attributeTexture  = 8;

    glBindAttribLocation(shader->shaderProgram, shader->attributePosition, "position");
    glBindAttribLocation(shader->shaderProgram, shader->attributeNormal, "normal");
    glBindAttribLocation(shader->shaderProgram, shader->attributeColor, "color");
    glBindAttribLocation(shader->shaderProgram, shader->attributeTexture, "texture");

    glLinkProgram(shader->shaderProgram);

    shader->uniformView = glGetUniformLocation( shader->shaderProgram, "modelview" );
    shader->uniformTexture0 = glGetUniformLocation( shader->shaderProgram, "colorTexture" );
    shader->uniformTexture1 = glGetUniformLocation( shader->shaderProgram, "depthTexture" );

    //fprintf(stderr, "attributePosition: %d\nattributeNormal: %d\nattributeColor: %d\nattributeTexture: %d\nuniformView: %d\nuniformTexture0: %d\nuniformTexture1: %d\n",
            //shader->attributePosition, shader->attributeNormal, shader->attributeColor, shader->attributeTexture, shader->uniformView, shader->uniformTexture0, shader->uniformTexture1);
}

void ex_use_shader(ex_shader_t* shader)
{
    glUseProgram(shader->shaderProgram);
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
            fprintf(stderr, "ERROR::PC SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::PC PROGRAM_LINKIN_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
}