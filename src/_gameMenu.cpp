#include "_gameMenu.h"

_gameMenu::_gameMenu()
{
    //ctor
}

_gameMenu::~_gameMenu()
{
    //dtor
}

void _gameMenu::drawSquare()
{
    glColor3f(1.0,1.0,1.0);
    mpTex->TextureBinder();  //binding the texture
    glBegin(GL_POLYGON);

    glTexCoord2f(0, 1);
    glVertex2f(-2, -1);
    glTexCoord2f(1, 1);
    glVertex2f(2, -1);
    glTexCoord2f(1, 0);
    glVertex2f(2, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-2, 1);

    glEnd();
}

void _gameMenu::menuPageInit(char* fileName)
{
    mpTex->loadTexture(fileName);  //load image by filename to pointer
}

