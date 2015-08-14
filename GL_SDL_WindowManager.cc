#include "GL_SDL_WindowManager.h"

#include "SDL_types.h"
#include "SDL.h"
#include "SDL_opengl.h"

bool GL_SDL_WindowManager::createWindow(int width, int height)
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult == -1) {
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_WM_SetCaption("Hello", NULL);
    Uint32 sdlVideoModeFlags = SDL_OPENGL | SDL_INIT_AUDIO;

    bool fullScreen = true;
    if (fullScreen) {
        sdlVideoModeFlags |= SDL_FULLSCREEN;
    }

    SDL_Surface *screen = SDL_SetVideoMode(width, 
                                           height,
		                           0,
		                           sdlVideoModeFlags
		                           );
    if (screen == NULL) {
        return false;
    }
 
    return true;
}


void GL_SDL_WindowManager::swapBuffers()
{
    SDL_GL_SwapBuffers();
}

