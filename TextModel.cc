#include "TextModel.h"
#include "SDLTextSurface.h"
#include "TextureUtil.h"

TextModel::TextModel(string text, float size)
{

    pointSize = size;
    z = -1.0f;
    glGenTextures(1, &texture);
    SDLTextSurface textSurface(text.c_str(), size);
    //textSurface.setFont("/usr/share/fonts/vlgothic/VL-Gothic-Regular.ttf"/*"arial.ttf"*/, pointSize);
    textSurface.setColor(255, 50, 0);
    SDL_Surface* surface = textSurface.getSurface();

    if (!surface) {
        printf("Can't get surface: \"%s\"\n",SDL_GetError()); 
        return;
    }

    width = surface->w;
    height = surface->h;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CreateTextBoxTexture(texture, surface);
 
    SDL_FreeSurface(surface);
}

void TextModel::transform()
{
}

void TextModel::draw()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
 
    glBegin(GL_QUADS);
   
    float factor = 1.05f;

    float h = height / (factor * 800.0f);
    float w = width / (factor * 600.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y - h, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + w, y - h, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + w, y, z);

    glEnd();
 
    glDisable(GL_TEXTURE_2D);
}
