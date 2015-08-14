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
    while (SDL_PollEvent(&sdlEvent)) {
        switch(sdlEvent.type) {
            case SDL_KEYDOWN:
                keyDownEvent();
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

