#ifndef __sdl_event_dispatcher__
#define __sdl_event_dispatcher__

#include "IEventHandler.h"

class SDLEventDispatcher {
public:
    SDLEventDispatcher();
    void pollEvents();
    void keyDownEvent();
    void setEventHandler(IEventHandler *handler) {
        eventHandler = handler;
    }
private:
    IEventHandler *eventHandler;
};

#endif

