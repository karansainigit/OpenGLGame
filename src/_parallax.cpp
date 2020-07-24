#include "_parallax.h"

//_textureLoader *bTex = new _textureLoader();

_parallax::_parallax()
{
    //ctor
    //initializing texture coordinates
    xMax = 0.0;
    yMax = 0.0;
    xMin = 1.0;
    yMin = 1.0;
}

_parallax::~_parallax()
{
    //dtor
}
void _parallax::drawSquare()
{

    glColor3f(1.0,1.0,1.0);
    bTex->TextureBinder();  //binding the texture

    glBegin(GL_POLYGON);
    glTexCoord2f(xMin, yMin);
    glVertex2f(-2, -1);
    glTexCoord2f(xMax, yMin);
    glVertex2f(2, -1);
    glTexCoord2f(xMax, yMax);
    glVertex2f(2, 1);
    glTexCoord2f(xMin, yMax);
    glVertex2f(-2, 1);
    glEnd();
}

void _parallax::parallaxInit(char* fileName)
{
    bTex->loadTexture(fileName);  //load image by filename to pointer

}
