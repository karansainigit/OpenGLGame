#ifndef _PARALLAX_H
#define _PARALLAX_H

#include <iostream>
#include <string>
#include <GL/gl.h>
#include <windows.h>
#include <SOIL.h>
#include <_textureLoader.h>

using namespace std;

class _parallax
{
    public:
        _parallax();
        virtual ~_parallax();

        void drawSquare();      //to draw a quad for the background
        void parallaxInit(char* );          //Load images to background

        _textureLoader *bTex = new _textureLoader();

        float xMax, yMax, xMin, yMin;       //for texture coordinates

    protected:

    private:
};

#endif // _PARALLAX_H
