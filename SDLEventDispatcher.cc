#include "SDLEventDispatcher.h"

#include "SDL_types.h"
#include "SDL.h"

SDLEventDispatcher::SDLEventDispatcher()
{
    eventHandler = 0;
}

void SDLEventDispatcher::pollEvents()
{
    SDL_Event sdlEvent;
    SDLKey key;

    while (SDL_PollEvent(&sdlEvent)) {
        switch(sdlEvent.type) {
            case SDL_KEYDOWN:
                keyDownEvent();
                break;

            case SDL_KEYUP:
                key = sdlEvent.key.keysym.sym;
                break;

            case SDL_QUIT:
                break;
            
            case SDL_MOUSEMOTION:
            {
                int dx = sdlEvent.motion.xrel;
                int dy = sdlEvent.motion.yrel;
            }
            break;
  
            case SDL_MOUSEBUTTONDOWN:
            {
                int x = sdlEvent.button.x;
                int y = sdlEvent.button.y;
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                {
                }
                else if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
                {
                }
                else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
                {
                }
                else if (sdlEvent.button.button == SDL_BUTTON_WHEELDOWN)
                {
                }
                else if (sdlEvent.button.button == SDL_BUTTON_WHEELUP)
                {
                }
            }
            break;
  
            case SDL_MOUSEBUTTONUP:
            {
                int x = sdlEvent.button.x;
                int y = sdlEvent.button.y;
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                {
                }
                else if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
                {
                }
                else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
                {
                }
            }
            break;
        }
    }
}

void SDLEventDispatcher::keyDownEvent()
{
    if (eventHandler) {
        eventHandler->keyPressed();
    }
}

