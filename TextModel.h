#ifndef __textmodel_h__
#define __textmodel_h__

#include "IModel.h"
#include <string>
using namespace std;
 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>

class TextModel : public IModel
{
public:
    TextModel(string text, float size);
    virtual void transform();
    virtual void draw();
    void setPosition(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    float getX() { return x; }
    float getY() { return y; }
    
private:
    GLuint texture;
    float x;
    float y;
    float z;
    float height;
    float width;
    float pointSize;
};

#endif
