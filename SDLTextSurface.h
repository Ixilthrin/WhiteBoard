#ifndef __sdl_text_surface__
#define __sdl_text_surface__

#include <string>
using namespace std;
 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>

class SDLTextSurface
{
public:
    SDLTextSurface(string text, int pointSize) 
    : _text(text)
    {
        TTF_Init();
        _font = TTF_OpenFont("/usr/share/fonts/vlgothic/VL-Gothic-Regular.ttf", pointSize);
    }

    void setFont(string path, int pointSize)
    { 
        _font = TTF_OpenFont(path.c_str(), pointSize);
    }

    void setColor(int red, int green, int blue)
    {
        _color.r = red;
        _color.g = green;
        _color.b = blue;
    }

    SDL_Surface* getSurface()
    {
        return TTF_RenderText_Blended(_font, _text.c_str(), _color);
    }

private:
    string _text;
    TTF_Font* _font;
    SDL_Color _color; 
};
 
#endif
