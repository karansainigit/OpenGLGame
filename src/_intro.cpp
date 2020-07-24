#include "_intro.h"

_intro::_intro()
{
    //ctor
    //initializing texture coordinates
    xMin = 0.0;
    yMin = 0.0;
    xMax = 1.0;
    yMax = 1.0;
}

_intro::~_intro()
{
    //dtor
}

void _intro::drawSquare()
{
    glColor3f(1.0,1.0,1.0);
    introTex->TextureBinder();     //binding the texture
    glBegin(GL_POLYGON);

    glTexCoord2f(xMin, yMax);
    glVertex2f(-2, -1);
    glTexCoord2f(xMax, yMax);
    glVertex2f(2, -1);
    glTexCoord2f(xMax, yMin);
    glVertex2f(2, 1);
    glTexCoord2f(xMin, yMin);
    glVertex2f(-2, 1);

    glEnd();
}

void _intro::introPageInit(char* fileName)
{
    introTex->loadTexture(fileName);   //load image by filename to pointer
}

void _intro::introscroll(bool Auto, string dir, float speed)
{
    if(Auto)        //to address automatic movement of the background
    {
        if(dir == "up")     //keyword "up"
        {
            yMin -= speed;
            yMax -= speed;
        }
        if(dir == "down")     //keyword "down"
        {
            yMin += speed;
            yMax += speed;
        }
        if(dir == "left")     //keyword "left"
        {
            xMin -= speed;
            xMax -= speed;
        }
        if(dir == "right")     //keyword "right"
        {
            xMin += speed;
            xMax += speed;
        }
    }
}
