#ifndef __texture_util_h__
#define __texture_util_h__

#include <GL/gl.h>
 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>

void CreateTextBoxTexture(GLuint& texture, SDL_Surface* surface);

#endif
