#include "_endPage.h"

_endPage::_endPage()
{
    //ctor
}

_endPage::~_endPage()
{
    //dtor
}

void _endPage::drawSquare(bool win)
{
    glColor3f(1.0,1.0,1.0);
    if(win)
        epTexWin->TextureBinder();     //binding the texture
    else
        epTexLose->TextureBinder();     //binding the texture

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

void _endPage::endPageInit(char* fileName1, char* fileName2)
{
    epTexWin->loadTexture(fileName1);   //load image by filename
    epTexLose->loadTexture(fileName2);   //load image by filename
}
