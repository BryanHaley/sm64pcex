#ifndef EX_OGL_H
#define EX_OGL_H

#if FOR_WINDOWS
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengl.h>

#else // For Non-Windows builds
#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1

#ifdef __APPLE__
#include <SDL2/SDL_opengl.h>
#else
#include <SDL2/SDL_opengles2.h>
#endif
#endif

#endif