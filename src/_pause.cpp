#include "_pause.h"

_pause::_pause()
{
    //ctor
}

_pause::~_pause()
{
    //dtor
}

void _pause::drawSquare()
{
    glColor3f(1.0,1.0,1.0);
    pauseTex->TextureBinder();      //binding the texture
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex2f(-2, -1);
    glTexCoord2f(1, 1);
    glVertex2f(+2, -1);
    glTexCoord2f(1, 0);
    glVertex2f(+2, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-2, 1);
    glEnd();
}

void _pause::initPause(char* fileName)
{
    pauseTex->loadTexture(fileName);    //load image by filename
}
