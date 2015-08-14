#ifndef __whiteboard_h__
#define __whiteboard_h__

#include "IProgram.h"

#include "GL_SDL_WindowManager.h"
#include "SDLTextSurface.h"
#include "TextureUtil.h"
#include "TextModel.h"
#include "frustum.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>

#include <stdio.h>
#include <math.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class WhiteBoard : public IProgram
{
public:
    WhiteBoard();
    virtual void run();
    void clearScreen();
    void addString(string s);
    string getUName() { return uname; }
    string getPWord() { return pword; }
private:
    GL_SDL_WindowManager *windowManager;
    Frustum *frustum;
    float screenWidth;
    float screenHeight;
    vector<string> strings;
    vector<TextModel *> textModels;
    string uname;
    string pword;
};


#endif
