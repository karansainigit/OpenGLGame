#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

#include <SOIL.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

class _textureLoader
{
    public:
        _textureLoader();
        virtual ~_textureLoader();

        void loadTexture(char *);   //loading image file
        void TextureBinder();       //binding the texture
        int width, height;      //width and height of image
        unsigned char *image;
        GLuint tex;

    protected:

    private:
};

#endif // _TEXTURELOADER_H
