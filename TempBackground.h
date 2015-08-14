#include "SDLTextSurface.h"
#include "TextureUtil.h"
 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_opengl.h>

#include <stdio.h>
#include <math.h>
#include <time.h>

#include <iostream>
using namespace std;

float ratio = 1;
float angle = 0.0f;
float zCam = -45;
float yRotation = 0.0f;
float camIncrement = .03;
int elementSize = 1;
int initialLines = 0;
int lineIncrementPerFrame = 1000;
float minZ = -45;
float maxZ = 2;
 
GLuint cloudTexture;
GLuint jetTexture;
GLuint moonTexture;

void createMoonSurface();

void init_background(void) {

    srand(time(0));

    SDL_Surface* cloudSurface = IMG_Load("clouds.jpg");
 
    glGenTextures(1, &cloudTexture);
    glBindTexture(GL_TEXTURE_2D, cloudTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cloudSurface->w, cloudSurface->h, 0, GL_RGB,GL_UNSIGNED_BYTE, cloudSurface->pixels);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    SDL_FreeSurface(cloudSurface);

    SDL_Surface* jetSurface = IMG_Load("jet.jpg");

    GLubyte checkImage[jetSurface->h][jetSurface->w][4];
    unsigned char *pixels = (unsigned char*) jetSurface->pixels;

   int index = 0;
   for (int i = 0; i < jetSurface->h; i++) {
      for (int j = 0; j < jetSurface->w; j++) {
         unsigned char r = checkImage[i][j][0] = pixels[index++];
         unsigned char g = checkImage[i][j][1] = pixels[index++];
         unsigned char b = checkImage[i][j][2] = pixels[index++];
         if (r > 240 && g > 240 && b > 240)
             checkImage[i][j][3] = 0; 
         else
             checkImage[i][j][3] = 250;
      }
   }

    glGenTextures(1, &jetTexture);
    glBindTexture(GL_TEXTURE_2D, jetTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, jetSurface->w, jetSurface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE, checkImage);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    SDL_FreeSurface(jetSurface);

    createMoonSurface();
}

void createMoonSurface()
{
    SDL_Surface* moonSurface = IMG_Load("moon.jpg");
 

    GLubyte checkImage[moonSurface->h][moonSurface->w][4];
    unsigned char *pixels = (unsigned char*) moonSurface->pixels;

   int index = 0;
   for (int i = 0; i < moonSurface->h; i++) {
      for (int j = 0; j < moonSurface->w; j++) {
         unsigned char r = checkImage[i][j][0] = pixels[index++];
         unsigned char g = checkImage[i][j][1] = pixels[index++];
         unsigned char b = checkImage[i][j][2] = pixels[index++];
         if (r > 240 && g > 240 && b > 240)
             checkImage[i][j][3] = 0; 
         else
             checkImage[i][j][3] = 80;
      }
   }

    glGenTextures(1, &moonTexture);
    glBindTexture(GL_TEXTURE_2D, moonTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, moonSurface->w, moonSurface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE, checkImage);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    SDL_FreeSurface(moonSurface);
}

void transformMoon()
{ 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawMoon()
{  
    glBindTexture(GL_TEXTURE_2D, moonTexture);
    glEnable(GL_TEXTURE_2D);
 
    glBegin(GL_QUADS);

    float z = -80;
    static float moonX = -25;
    static float moonY = 20;
    float moonWidth = 25;
    float moonHeight = 20;

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(moonX, moonY, z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(moonX, moonY - moonHeight, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(moonX - moonWidth, moonY - moonHeight, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(moonX - moonWidth, moonY, z);

    glEnd();

    moonY += .001;
    moonX += .002;
}

void transformClouds()
{ 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawClouds()
{  
    glBindTexture(GL_TEXTURE_2D, cloudTexture);
    glEnable(GL_TEXTURE_2D);
 
    glBegin(GL_QUADS);

    float x = 60;
    float y = 60;
    float z = -90;

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, y, z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, -y, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, -y, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z);

    glEnd();
}

float jetX = 100;
float y = 0;
float z = 0;

void transformJet()
{ 
    if (jetX > 90)
    {
        y = (float) (rand() % 40 - 20);
        z = (float) (1 + rand() % 70);
        jetX = -200;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(jetX, y, -z);
    jetX += .2;
}

void drawJet()
{  
    glBindTexture(GL_TEXTURE_2D, jetTexture);
    glEnable(GL_TEXTURE_2D);
 
    glBegin(GL_QUADS);

    float x = 2;
    float y = 2;
    float z = -10;

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, y, z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, -y, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, -y, z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z);

    glEnd();
}

void draw_background() 
{
    transformClouds();
    drawClouds();
    transformMoon();
    drawMoon();
    transformJet();
    drawJet();
}
