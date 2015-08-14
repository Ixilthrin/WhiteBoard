#ifndef _GL_SDL_WINDOW_MANAGER_H
#define _GL_SDL_WINDOW_MANAGER_H

/**
 *  Concrete class for creating a window using SDL with OpenGL
 */
class GL_SDL_WindowManager
{
public:
    bool createWindow(int width = 500, int height = 500);
    void swapBuffers();
};

#endif

