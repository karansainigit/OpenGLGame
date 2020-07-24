#include "_helpPage.h"

_helpPage::_helpPage()
{
    //ctor
}

_helpPage::~_helpPage()
{
    //dtor
}


void _helpPage::drawSquare()
{
    glColor3f(1.0,1.0,1.0);
    hpTex->TextureBinder();     //binding the texture
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

void _helpPage::helpPageInit(char* fileName)
{
    hpTex->loadTexture(fileName);   //load image by filename to pointer
}
