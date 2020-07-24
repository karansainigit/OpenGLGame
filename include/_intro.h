#ifndef _INTRO_H
#define _INTRO_H

#include <_textureLoader.h>

class _intro
{
    public:
        _intro();
        virtual ~_intro();

        void drawSquare();  //to draw a quad for the background
        void introPageInit(char* );   //Load images to background
        void introscroll(bool, string, float); //bool for Auto, string for direction, speed of the movement

        _textureLoader *introTex = new _textureLoader();   //creating pointer for texture loader

        float xMax, yMax, xMin, yMin;   //for texture coordinates

    protected:

    private:
};

#endif // _INTRO_H
